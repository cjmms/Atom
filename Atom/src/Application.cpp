/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
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

string musicTrackIntro = "Atom/res/audio/suspense_loop.wav";
string musicTrackGame = "Atom/res/audio/atom_space_jump_ambient.wav";
string sfxClick = "Atom/res/audio/menu_click.wav";
string sfxDeath = "Atom/res/audio/death.wav";
string dialogueTrack = "Atom/res/audio/optimus_speech.ogg";
string sfxJump = "Atom/res/audio/jump.ogg";
string sfxLand = "Atom/res/audio/land.ogg";
string sfxBullet = "Atom/res/audio/bulletshot.mp3";
ChannelID musicChannelID = -1;
ChannelID sfxChannelID = -1;
ChannelID dialogueChannelID = -1;
float musicVolumedB = 0.1f;
float sfxVolumedB = 0.04f;
float dialogueVolumedB = 0.0f;
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
    ae.setMaxFPS(120);                       // set the fps
    ae.printGraphicsInfo();                 // print OpenGL info

    ae.loadSound(musicTrackIntro,true);
    ae.loadSound(musicTrackGame, true);
    ae.loadSound(dialogueTrack);
    ae.loadSound(sfxClick);
    ae.loadSound(sfxDeath);
    ae.loadSound(sfxJump);
    ae.loadSound(sfxLand);
    ae.loadSound(sfxBullet);

    ae.mLevelManager->startGame();

    //musicChannelID = ae.play(musicTrackIntro, ChannelGroupTypes::C_MUSIC, musicVolumedB,-1);
    //sfxChannelID = ae.play(sfxJump, ChannelGroupTypes::C_MUSIC, sfxVolumedB,0);
    //dialogueChannelID = ae.play(dialogueTrack, ChannelGroupTypes::C_DIALOGUE, dialogueVolumedB,0);

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
    if (ae.mLevelManager->level > COUNT_INTROS - 1 && ae.mLevelManager->level < ED_LEVELS) {
        ae.mUIManager->drawText(5, 15, (string("LEVEL : ") + std::to_string(ae.mLevelManager->level - COUNT_INTROS + 1)).c_str());
        ae.mUIManager->drawText(5, 25, (string("TIME ELAPSED : ") + std::to_string(ae.getUptime() - ae.mLevelManager->levelStartTime) + string("s")).c_str());
    }
}

bool menu_start = true;
bool menu_ingame = false;
char buttontext[40] = "PLAY";
bool menu_inprogress = false;

void playMenuclick() {
    ae.play(sfxClick, ChannelGroupTypes::C_SFX, 0.2f + sfxVolumedB);
}

void initSpectrum(){
    for (int i = 0; i < 100; ++i) {
        EntityID rectangle = ae.createEntity();
        ae.addComponent(rectangle, RectangleComponent{
            glm::vec3{0.5,1,1},   //colors
            false
            });
        ae.addComponent(rectangle, TransformComponent{
            glm::vec3{-1.0f + 0.0250 * i, 0, 0}, // position
            glm::vec3{0.0f,0.0f,0.0f}, // rotation
            glm::vec3{0.005f,0.01f,0.5f},  // scale 
            glm::mat4(1.0f)
            });
        ae.addComponent(rectangle, ShapeComponent{ ShapeType::AABB });
        ae.addComponent(rectangle, PhysicsBodyComponent(1, true));
    }
}

void showGameMenu() {
     // now we are in menu
    if (ae.mLevelManager->level == COUNT_INTROS-1) {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 175, ImGui::GetIO().DisplaySize.y / 2 - 215));
        ImGui::Begin("SPACE JUMP", NULL, 
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBackground | 
            ImGuiWindowFlags_NoTitleBar | 
            ImGuiWindowFlags_NoMove | 
            //ImGuiWindowFlags_NoInputs | 
            //ImGuiWindowFlags_NoScrollbar |
            //ImGuiWindowFlags_AlwaysAutoResize
            ImGuiWindowFlags_NoResize
        );
        //ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5, 0.5);
        ImVec2 p;
        p.x = ImGui::GetWindowWidth() / 2;
        int button_width = ImGui::GetWindowWidth();
        int button_height = 40;


        if ((menu_start && !menu_ingame) || menu_inprogress) {
            if (menu_inprogress) {
                sprintf(buttontext, "Loading %c", "|/-\\"[(int)(ImGui::GetTime() / 0.05f) & 3]);
            }
            else {
                sprintf(buttontext, "PLAY");
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button(buttontext,ImVec2(button_width,button_height))) {
                playMenuclick();
                menu_inprogress = true;
                ae.mLevelManager->loadNextLevel();
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("CONTROLS", ImVec2(button_width, button_height))) {
                playMenuclick();
                ae.mLevelManager->loadLevel(COUNT_INTROS - 2);
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("CREDITS",ImVec2(button_width,button_height))) {
                playMenuclick();
                menu_inprogress = true;
                ae.mLevelManager->loadLevel(ED_LEVELS);
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("EXIT", ImVec2(button_width, button_height))) {
                playMenuclick();
                ae.mIsRunning = false;
            }
        }
        ImGui::End();
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
    ae.mUIManager->addUIPainter(showGameMenu);


    while (ae.mIsRunning) {
        glfwpoll();      
        ae.update();
        fpsCounter();
    }

    shutdown();
    return 0;
}