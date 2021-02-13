/*
* @file		AudioManager.cpp
* @author	Abhikalp Unakal
* @brief	Audio Manager to deal with low level channels, samples and DSP's
* @date		2021-02-10
*/

#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "core/Event.hpp"
#include "utils/Log.hpp"

inline int FMOD_ERROR(FMOD_RESULT res) {
	if (res != FMOD_OK) {
		ATOM_ERROR("FMOD : {}", FMOD_ErrorString(res));
		return 1;
	}
	return 0;
}

class AudioManager {
public:

	// class functions
	AudioManager() {

	}
	~AudioManager() {
		FMOD_ERROR(mMasterChannelGroup->removeDSP(mDSP));
		FMOD_ERROR(mDSP->release());
		FMOD_ERROR(mCoreSystem->close());
		FMOD_ERROR(mCoreSystem->release());
	}
	inline void init() {
		// setup core system
		FMOD_ERROR(FMOD::System_Create(&mCoreSystem));
		FMOD_ERROR(mCoreSystem->init(FMODMAXCHANNELS, FMOD_INIT_NORMAL, 0));
		assert(mCoreSystem != NULL);
		// get a handle to master channel 
		FMOD_ERROR(mCoreSystem->getMasterChannelGroup(&mMasterChannelGroup));
		// create subchannels
		FMOD_ERROR(mCoreSystem->createChannelGroup("SFX Channel",&mSFXChannelGroup));
		FMOD_ERROR(mCoreSystem->createChannelGroup("Music Channel", &mMusicChannelGroup));
		// create sub channel hierarchy
		FMOD_ERROR(mMasterChannelGroup->addGroup(mSFXChannelGroup));
		FMOD_ERROR(mMasterChannelGroup->addGroup(mMusicChannelGroup));
		// attach DSP's to subchannel groups
		FMOD_ERROR(mCoreSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &mDSP));
		FMOD_ERROR(mMasterChannelGroup->addDSP(0, mDSP));
	}

	inline void update() {
		std::vector<ChannelID> stoppedChannels;

		for (auto& it : mChannelPool) {
			bool playing = false;
			it.second->isPlaying(&playing);
			if (!playing) {
				stoppedChannels.push_back(it.first);
			}
		}

		for (auto& sc : stoppedChannels) {
			mChannelPool.erase(sc);
		}
		FMOD_ERROR(mCoreSystem->update());
	}

	inline FMOD::Sound* loadSound(string audioloc, 
		FMOD_MODE _mode = FMOD_DEFAULT | FMOD_3D | FMOD_LOOP_OFF | FMOD_CREATECOMPRESSEDSAMPLE,
		FMOD_CREATESOUNDEXINFO* _exinfo = NULL) {
		if (mSoundPool.count(audioloc) > 0) {
			return mSoundPool[audioloc];
		}
		FMOD::Sound* asound = NULL;
		FMOD_ERROR(mCoreSystem->createSound(audioloc.c_str(),_mode,_exinfo,&asound));
		if (asound != NULL) {
			mSoundPool[audioloc] = asound;
		}
		return asound;
	}

	inline void unloadSound(string audioloc) {
		if (mSoundPool.count(audioloc) > 0) {
			mSoundPool[audioloc]->release();
			mSoundPool.erase(audioloc);
		}
	}	
	
	inline ChannelID play(string audioloc, ChannelGroupTypes cgtype, float volumedB=0.0f) {
		ChannelID currentChannelID = mChannelID++;
		FMOD::Channel* currentChannel = NULL;
		FMOD::ChannelGroup* channelgroup = NULL;
		channelgroup = cgtype == ChannelGroupTypes::C_SFX ? mSFXChannelGroup : NULL;
		channelgroup = cgtype == ChannelGroupTypes::C_MUSIC ? mMusicChannelGroup : NULL;
		if (mSoundPool.count(audioloc) > 0) {
			FMOD_ERROR(mCoreSystem->playSound(mSoundPool[audioloc], channelgroup, true, &currentChannel));
		}
		if (currentChannel != NULL) {
			FMOD_ERROR(currentChannel->setVolume(volumedB));
			FMOD_ERROR(currentChannel->setPaused(false));
			mChannelPool[currentChannelID] = currentChannel;
		}
		return currentChannelID;
	}

	bool isPlaying(ChannelID channelid) {
		bool playing = false;
		if (mChannelPool.count(channelid) > 0) {
			mChannelPool[channelid]->isPlaying(&playing);
			return playing;
		}
		return playing;
	}

	void pause(ChannelID channelid) {
		bool paused = true;
		if (mChannelPool.count(channelid) > 0) {
			mChannelPool[channelid]->setPaused(&paused);
		}
	}

	void stop(ChannelID channelid) {
		if (mChannelPool.count(channelid) > 0) {
			mChannelPool[channelid]->stop();
		}
	}

	void stopAllChannels() {
		for (auto& channel : mChannelPool) {
			channel.second->stop();
			--mChannelID;
		}
	}

	inline void setChannelVolumedB(ChannelID channelid, float volumedB) {
		// if channel exists in our pool
		//assert(mChannelPool.count(channelid) > 0 && "Channel does not exist");
		mChannelPool[channelid]->setVolume(volumedB);
		return;
	}

	inline float getChannelVolumedB(ChannelID channelid) {
		// if channel exists in our pool
		assert(mChannelPool.count(channelid) > 0 && "Channel does not exist");
		float vol = 0.0;
		mChannelPool[channelid]->getVolume(&vol);
		return vol;
	}

	inline float dbToVol(float dB) {
		return (float)powf(10.0f,0.05 * dB);
	}

	inline float volTodB(float vol) {
		return 20.0f * log10f(vol);
	}

	FMOD_DSP_PARAMETER_FFT* fft() {
		FMOD_DSP_PARAMETER_FFT* fftdata;
		int length = 512;
		mDSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&fftdata, 0, 0, 0);
		return fftdata;
	}


	inline void onEvent(Event& e) {
		// dispatch events 
	}
	
	FMOD::DSP* mDSP = NULL;
	
	FMOD::ChannelGroup* mMasterChannelGroup = NULL;
	FMOD::ChannelGroup* mSFXChannelGroup = NULL;
	FMOD::ChannelGroup* mMusicChannelGroup = NULL;

	ChannelID mChannelID = 0;
	SoundID mSoundID = 0;

	ChannelMap mChannelPool;
	SoundMap mSoundPool;

	FMOD::System* mCoreSystem = NULL;

};





#endif