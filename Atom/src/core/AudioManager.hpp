#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "core/Event.hpp"
#include "utils/Log.hpp"
#include "utils/ResourceLoader.hpp"

inline int FMOD_ERROR(FMOD_RESULT res) {
	if (res != FMOD_OK) {
		ATOM_ERROR("FMOD : {}", FMOD_ErrorString(res));
		return 1;
	}
	return 0;
}

class AudioManager {
public:
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
		assert(mSystem != NULL);
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
		std::vector<ChannelMap::iterator> stoppedChannels;
		for (auto it = mChannels.begin(); it != mChannels.end(); ++it) {
			bool isPlaying = false;
			it->second->isPlaying(&isPlaying);
			if (!isPlaying) {
				stoppedChannels.push_back(it);
			}
		}
		for (auto& it : stoppedChannels) {
			mChannels.erase(it);
		}
		FMOD_ERROR(mCoreSystem->update());
	}
	inline void onEvent(Event& e) {
		// dispatch events 
	}
	
	FMOD::DSP* mDSP = NULL;
	
	FMOD::ChannelGroup* mMasterChannelGroup = NULL;
	FMOD::ChannelGroup* mSFXChannelGroup = NULL;
	FMOD::ChannelGroup* mMusicChannelGroup = NULL;

	ChannelID mChannelID;
	ChannelMap mChannels;
	FMOD::System* mCoreSystem = NULL;

};





#endif