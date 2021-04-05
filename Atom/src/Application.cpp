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

// THE ENGINE
AtomEngine ae;

void shutdown();


#ifdef _WIN64
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

//allocating console
void console() {
#ifdef _WIN64
    if (AllocConsole())
    {
        FILE* file;

        freopen_s(&file, "CONOUT$", "wt", stdout);
        freopen_s(&file, "CONOUT$", "wt", stderr);
        freopen_s(&file, "CONOUT$", "wt", stdin);

        SetConsoleTitle(L"[ATOM]");
    }
#endif
}

// max 80 limit
void setConsoleTitle(const char* title) {
#ifdef _WIN64
    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout.imbue(std::locale("en_US.utf8"));
    wchar_t wstr[80];
    // +1 to account for \0 termination
    size_t wsize;
    mbstowcs_s(&wsize, wstr, strlen(title) + 1, title, strlen(title));
    SetConsoleTitle(wstr);
#endif
}


// performance data
void fpsCounter() {
    char title[MAX_TITLE_LEN];
    snprintf(title, MAX_TITLE_LEN, "[ATOM] FPS: %f", ae.getFPS());
#ifdef _WIN64
    setConsoleTitle(title);
#else
    ATOM_TRACE("[ATOM] FPS: {}", ae.getFPS());
#endif
}




string musicTrack = "Atom/res/audio/wariyo_mortals.ogg";
string sfxTrack = "Atom/res/audio/optimus_speech.ogg";

string sfxJump = "Atom/res/audio/EllenFootstepJump.ogg";
string sfxLand = "Atom/res/audio/EllenFootstepLand.ogg";
string sfxBullet = "Atom/res/audio/bullet-retro-gun-shot.mp3";

ChannelID musicChannelID = -1;
ChannelID sfxChannelID = -1;

static float musicVolumedB = 0.0f;
static float sfxVolumedB = 0.1f;
static float listenerXOffset = 0.0f;
static float listenerYOffset = 0.0f;
static float listenerOffset[] = { 0.0f,0.0f };

static FMOD_VECTOR listener_position{ 0.0f,0.0f,0.0f };
static FMOD_VECTOR listener_fwd{ 0.0f,0.0f,1.0f };
static FMOD_VECTOR listener_up{ 0.0f,1.0f,0.0f };
static float listener_step = 0.1f;

bool checkCloseWindow = false;
bool checkRestartWindow = false;

void uiDraw() {

    if (ae.mIsPaused) {

        //render your GUI
        ImGui::Begin(
            "Menu",
            0,
            ImGuiWindowFlags_NoCollapse
        );
        ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
        ImGui::SliderFloat("SPEECH VOLUME", &sfxVolumedB, 0.0f, 1.0f);
        ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

        ae.setVolume(musicChannelID, musicVolumedB);
        ae.setVolume(sfxChannelID, sfxVolumedB);
        ae.listener3DSetXOffset(listenerOffset[0]);
        ae.listener3DSetYOffset(listenerOffset[1]);


        if (ImGui::Button("Quit Game"))
        {
            checkCloseWindow = true;
        }

        if (ImGui::Button("Resume Game"))
        {
            ae.mIsPaused = false;
        }

        if (ImGui::Button("Restart Current Level"))
        {
            checkRestartWindow = true;

            //ae.mLevelManager->restartCurrentLevel();
            //ae.mIsPaused = false;   // close the menu
        }
        ImGui::End();

        // check if the player wants to end the game
        if (checkCloseWindow) {
            ImGui::Begin("", &checkCloseWindow, ImGuiWindowFlags_NoCollapse);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Are you sure you want to quit the game?");

            if (ImGui::Button("Yes")) ae.mIsRunning = false;
            if (ImGui::Button("No")) checkCloseWindow = false;
            ImGui::End();
        }

        // check if the player wants to restart the menu
        if (checkRestartWindow)
        {
            ImGui::Begin("", &checkRestartWindow, ImGuiWindowFlags_NoCollapse);
            ImGui::Text("Are you sure you want to restart the level? Current progress will lost.");
            if (ImGui::Button("Yes"))
            {
                ae.mLevelManager->restartCurrentLevel();
                ae.mIsPaused = false;   // close the menu
            }
            if (ImGui::Button("No")) checkRestartWindow = false;

            ImGui::End();
        }

    }
}


void glfwpoll() {
    glfwPollEvents();
    if (ae.mGraphicsManager->shouldWindowClose()) {
        ae.mIsRunning = false;
    }
}

void start() {
    console();                              // setup the console 
    Log::init();                            // setup logging

    ae.init();                              // initialize engine
    ae.setMaxFPS(120);                       // set the fps
    ae.printGraphicsInfo();                 // print OpenGL info
    ae.mUIManager->addUIPainter(uiDraw);    // add ui painter to list
    
    ae.loadSound(musicTrack);
    ae.loadSound(sfxTrack);
    ae.loadSound(sfxJump);
    ae.loadSound(sfxLand);
    ae.loadSound(sfxBullet);


    ae.mLevelManager->load(0);

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


int main(int argc, char** argv){
    
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
