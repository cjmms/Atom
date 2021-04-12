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




char title[MAX_TITLE_LEN];
// performance data
void fpsCounter() {
    snprintf(title, MAX_TITLE_LEN, "FPS: %f", ae.getFPS());
#ifdef _WIN64
    #ifdef DEBUG
    setConsoleTitle(title);
    #endif
#else
    ATOM_TRACE("{} FPS: {}", APPNAME, ae.getFPS());
#endif
}

extern string musicTrack;
extern string sfxTrack;
extern string sfxJump;
extern string sfxLand;
extern string sfxBullet;
extern ChannelID musicChannelID;
extern ChannelID sfxChannelID;
extern float musicVolumedB;
extern float sfxVolumedB;
extern float dialogVolumedB;
extern float listenerXOffset;
extern float listenerYOffset;
extern float listenerOffset[];
extern FMOD_VECTOR listener_position;
extern FMOD_VECTOR listener_fwd;
extern FMOD_VECTOR listener_up;
extern float listener_step;


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
    ae.setMaxFPS(120);                       // set the fps
    ae.printGraphicsInfo();                 // print OpenGL info

    ae.loadSound(musicTrack);
    ae.loadSound(sfxTrack);
    ae.loadSound(sfxJump);
    ae.loadSound(sfxLand);
    ae.loadSound(sfxBullet);

    ae.mLevelManager->startGame();

    musicChannelID = ae.play(musicTrack, ChannelGroupTypes::C_MUSIC, musicVolumedB);
    sfxChannelID = ae.play(sfxTrack, ChannelGroupTypes::C_DIALOGUE, 0.0f);

}

void shutdown() {
    // save progress unload memory and shutdown
    ae.mLevelManager->save();
    ae.mLevelManager->unload();
    ae.shutdown();
    Log::shutdown();
}
int totaltime = 0;

void printScore() {
    if (ae.mIsDebugMode) {
        ae.mUIManager->drawText(5, 5, title);
    }
    if (ae.mLevelManager->level > 1) {
        ae.mUIManager->drawText(5, 15, (string("LEVEL : ") + std::to_string(ae.mLevelManager->level)).c_str());
        ae.mUIManager->drawText(5, 25, (string("TIME ELAPSED : ") + std::to_string(ae.getUptime() - ae.mLevelManager->levelStartTime) + string("s")).c_str());
    }
}

void showGameMenu() {
    // now we are in menu
    if (ae.mLevelManager->level == 2) {
        ImGui::Button
    }
}


#ifdef DEBUG
int main(int argc, char** argv){
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) {
#endif
    // Setup memory leak dump 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    start();
    ae.mUIManager->addUIPainter(printScore);

    while (ae.mIsRunning) {
        glfwpoll();      
        ae.update();
        fpsCounter();
    }

    shutdown();
    return 0;
}