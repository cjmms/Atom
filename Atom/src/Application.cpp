/*
* @file		Application.cpp
* @author	Abhikalp Unakal
* @brief	main bootstrapper
* @date		2021-01-12
*/
#define _CRTDBG_MAP_ALLOC
#include <Pch.hpp>
#include <crtdbg.h>
#include <cstdlib>
#include <clocale>

#include "core/AtomEngine.hpp"
#include "systems/ParticleEffect/ParticleEffect.hpp"

// THE ENGINE
AtomEngine ae;


#ifdef _WIN64
#ifdef DEBUG
#include "Windows.h"
FILE _iob[] = {
    *stdin,
    *stdout,
    *stderr
};
extern "C" FILE * __cdecl __iob_func(void) {
    return _iob;
}
#pragma comment(lib, "legacy_stdio_definitions.lib")
#endif
#endif

//allocating console
void console() {
#ifdef _WIN64
#ifdef DEBUG
    if (AllocConsole())
    {
        FILE* file;

        freopen_s(&file, "CONOUT$", "wt", stdout);
        freopen_s(&file, "CONOUT$", "wt", stderr);
        freopen_s(&file, "CONOUT$", "wt", stdin);
        wchar_t wstr[80];
        // +1 to account for \0 termination
        size_t wsize;
        string title = APPNAME;
        mbstowcs_s(&wsize, wstr, strlen(title.c_str()) + 1, title.c_str(), strlen(title.c_str()));
        SetConsoleTitle(wstr);
    }
#endif
#endif
}

// max 80 limit
void setConsoleTitle(const char* title) {
#ifdef _WIN64
#ifdef DEBUG
    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout.imbue(std::locale("en_US.utf8"));
    wchar_t wstr[80];
    // +1 to account for \0 termination
    size_t wsize;
    mbstowcs_s(&wsize, wstr, strlen(title) + 1, title, strlen(title));
    SetConsoleTitle(wstr);
#endif
#endif
}


// performance data
void fpsCounter() {
    char title[MAX_TITLE_LEN];
    snprintf(title, MAX_TITLE_LEN, "FPS: %f", ae.getFPS());
#ifdef _WIN64
    #ifdef DEBUG
    setConsoleTitle(title);
    #endif
#else
    ATOM_TRACE("{} FPS: {}", APPNAME, ae.getFPS());
#endif
}




string musicTrack = "Atom/res/audio/wariyo_mortals.ogg";
string sfxTrack = "Atom/res/audio/optimus_speech.ogg";

string sfxJump = "Atom/res/audio/EllenFootstepJump.ogg";
string sfxLand = "Atom/res/audio/EllenFootstepLand.ogg";
string sfxBullet = "Atom/res/audio/bullet-retro-gun-shot.mp3";

ChannelID musicChannelID = -1;
ChannelID sfxChannelID = -1;

float musicVolumedB = 0.0f;
float sfxVolumedB = 0.1f;
float listenerXOffset = 0.0f;
float listenerYOffset = 0.0f;
float listenerOffset[] = { 0.0f,0.0f };

FMOD_VECTOR listener_position{ 0.0f,0.0f,0.0f };
FMOD_VECTOR listener_fwd{ 0.0f,0.0f,1.0f };
FMOD_VECTOR listener_up{ 0.0f,1.0f,0.0f };
float listener_step = 0.1f;


void glfwpoll() {
    glfwPollEvents();
    if (ae.mGraphicsManager->shouldWindowClose()) {
        ae.mIsRunning = false;
    }
}

void start() {
#ifdef DEBUG
    console();                              // setup the console 
    Log::init();                            // setup logging
#endif

    ae.init();                              // initialize engine
    ae.setMaxFPS(60);                       // set the fps
    ae.printGraphicsInfo();                 // print OpenGL info

    ae.loadSound(musicTrack);
    ae.loadSound(sfxTrack);
    ae.loadSound(sfxJump);
    ae.loadSound(sfxLand);
    ae.loadSound(sfxBullet);

    ae.mLevelManager->startGame();

    musicChannelID = ae.play(musicTrack, ChannelGroupTypes::C_MUSIC, 0.0f);
    sfxChannelID = ae.play(sfxTrack, ChannelGroupTypes::C_SFX, 0.0f);

}

void shutdown() {
    // save progress unload memory and shutdown
    ae.mLevelManager->save();
    ae.mLevelManager->unload();
    ae.shutdown();
    Log::shutdown();
}


#ifdef DEBUG
int main(int argc, char** argv){
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) {
#endif
    // Setup memory leak dump 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    start();

    while (ae.mIsRunning) {
        glfwpoll();      
        ae.update();
        fpsCounter();
    }

    shutdown();
    return 0;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
//
//    // Setup memory leak dump 
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//    start();
//
//    while (ae.mIsRunning) {
//        glfwpoll();
//        ae.update();
//        fpsCounter();
//    }
//
//    shutdown();
//    return 0;
//}

