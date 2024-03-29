/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		UIManager.cpp
* @author	Abhikalp Unakal
* @brief	UI Orchestrator
* @date		2021-04-09
*/

#include <Pch.hpp>
#include "UIManager.hpp"
#include "AtomEngine.hpp"


extern AtomEngine ae;

extern string sfxClick;
extern ChannelID musicChannelID;
extern ChannelID sfxChannelID;
extern ChannelID dialogueChannelID;
extern float musicVolumedB;
extern float sfxVolumedB;
extern float dialogueVolumedB;
extern float listenerOffset[];
extern bool menu_start;
extern bool menu_inprogress;
void playMenuClick() {
    ae.play(sfxClick, ChannelGroupTypes::C_SFX, 0.2f + sfxVolumedB);
}

void UIManager::init(GLFWwindow* window) {
    const char* glsl_version = "#version 430";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::GetIO().IniFilename = NULL;
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

}


UIManager::~UIManager(){
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::drawText(int x, int y, const char* string){
    ImVec2 p;
    p.x = float(x);
    p.y = float(y);
    ImGui::SetNextWindowPos(ImVec2(10,10));
    ImGui::SetNextWindowSize(ImVec2(181, 46));
    ImGui::Begin("OVERLAY", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPos(p);
    ImGui::Text("%s", string);
    ImGui::End();
}

void UIManager::update(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // if the game is not paused, do not show menu UI
    if (ae.mIsPaused) {
        if (!ae.mIsControlsShowed) {
            showMenu();
        }
        // check if the player wants to end the game
        if (checkCloseWindow) showCheckCloseWindow();

        // check if the player wants to restart the menu
        if (checkRestartWindow) showCheckRestartWindow();

        if (checkRestartGame) showCheckRestartGame();

        if (checkExitToMainMenu) showCheckExitToMainMenuWindow();

    }
    else {
        for (auto& painter : mUIPainters) {
            painter();
        }
    }

    if (!ae.mIsPaused && ae.mIsControlsShowed) {
        showMenu();
    }
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::closeWindow(){
    ae.mIsPaused = true;
    checkCloseWindow = true;
}

void UIManager::addUIPainter(const std::function<void()>& uiPainter){

    mUIPainters.insert(uiPainter);
}

void UIManager::removeUIPainter(const std::function<void()>& uiPainter){
    mUIPainters.erase(uiPainter);
}



void UIManager::showMenu(){
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 175, ImGui::GetIO().DisplaySize.y / 2 - 215));
    ImGui::SetNextWindowSize(ImVec2(350,470));
    //render your GUI
    ImGui::Begin("MENU", 0, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );
    ImVec2 p;
    p.x = ImGui::GetWindowWidth() / 2;
    int button_width = ImGui::GetWindowWidth();
    int button_height = 40;

    if(ae.mIsControlsShowed) {
        ImGui::SetCursorPosX(p.x - (button_width / 2));
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - button_height - 10);
        if (ImGui::Button("HIDE CONTROLS", ImVec2(button_width, button_height))) {
            playMenuClick();
            ae.mIsPaused = false;
            ae.mIsControlsShowed = false;
        }
    }
    else {
        if (ae.mIsOptionsShowed) {
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("HIDE OPTIONS", ImVec2(button_width, button_height))) {
                playMenuClick();
                ae.mIsOptionsShowed = false;
                if (ae.mLevelManager->level == COUNT_INTROS-1) {
                    ae.mIsPaused = false;
                }
            }
            if (ae.mGraphicsManager->mFullscreen) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("WINDOWED MODE", ImVec2(button_width, button_height))) {
                    playMenuClick();

                    if (ae.mLevelManager->level == COUNT_INTROS - 1) {
                        ae.mLevelManager->restartCurrentLevel();
                    }
                    ae.mGraphicsManager->WindowMode();
                }
            }
            if (!ae.mGraphicsManager->mFullscreen) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("FULLSCREEN MODE", ImVec2(button_width, button_height))) {
                    playMenuClick();
                    if (ae.mLevelManager->level == COUNT_INTROS - 1) {
                        ae.mLevelManager->restartCurrentLevel();
                    }
                    ae.mGraphicsManager->FullScreenMode();
                }
            }
            // Audio UI setup
            if (ae.mIsMuted) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("UNMUTE AUDIO", ImVec2(button_width, button_height)))
                {
                    playMenuClick();
                    ae.mIsMuted = false;
                    ae.mAudioManager->mMasterChannelGroup->setMute(ae.mIsMuted);
                    checkCloseWindow = false;   // disable other window
                    checkRestartGame = false;
                    checkExitToMainMenu = false;
                    checkRestartWindow = false;
                    ae.mIsPaused = false;
                }
            }
            else {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("MUTE AUDIO", ImVec2(button_width, button_height)))
                {
                    playMenuClick();
                    ae.mIsMuted = true;
                    ae.mAudioManager->mMasterChannelGroup->setMute(ae.mIsMuted);
                    checkCloseWindow = false;   // disable other window
                    checkRestartGame = false;
                    checkExitToMainMenu = false;
                    checkRestartWindow = false;
                    ae.mIsPaused = false;
                }
            }

            ImGui::SetCursorPosX(p.x - (button_width / 2));
            ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            ImGui::SliderFloat("SFX VOLUME", &sfxVolumedB, 0.0f, 1.0f);
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            //ImGui::SliderFloat("SPEECH VOLUME", &dialogueVolumedB, 0.0f, 1.0f);
            //ImGui::SetCursorPosX(p.x - (button_width / 2));
            ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

            ae.setVolume(musicChannelID, musicVolumedB);
            ae.setVolume(sfxChannelID, sfxVolumedB);
            ae.setVolume(dialogueChannelID, dialogueVolumedB);
            ae.listener3DSetXOffset(listenerOffset[0]);
            ae.listener3DSetYOffset(listenerOffset[1]);
        }
        else {
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("SHOW OPTIONS", ImVec2(button_width, button_height))) {
                playMenuClick();
                ae.mIsOptionsShowed = true;
            }

            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("RESUME GAME", ImVec2(button_width, button_height)))
            {
                playMenuClick();
                checkRestartWindow = false;  // disable other window
                checkRestartGame = false;
                checkCloseWindow = false;    // disable other window
                checkExitToMainMenu = false;
                ae.mIsPaused = false;
            }

            if (!ae.mIsControlsShowed) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("SHOW CONTROLS", ImVec2(button_width, button_height))) {
                    playMenuClick();
                    ae.mIsPaused = false;
                    ae.mIsControlsShowed = true;
                }
            }
            if (ae.mLevelManager->level >= COUNT_INTROS && ae.mLevelManager->level < ED_LEVELS) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("RESTART CURRENT LEVEL", ImVec2(button_width, button_height)))
                {
                    playMenuClick();
                    checkCloseWindow = false;   // disable other window
                    checkRestartGame = false;
                    checkExitToMainMenu = false;
                    checkRestartWindow = true;
                }

                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("RESTART GAME", ImVec2(button_width, button_height)))
                {
                    playMenuClick();
                    checkCloseWindow = false;   // disable other window
                    checkRestartWindow = false;
                    checkExitToMainMenu = false;
                    checkRestartGame = true;
                }
            }
            if (ae.mLevelManager->level >= COUNT_INTROS) {
                ImGui::SetCursorPosX(p.x - (button_width / 2));
                if (ImGui::Button("EXIT TO MAIN MENU", ImVec2(button_width, button_height))) {

                    playMenuClick();
                    checkExitToMainMenu = true;
                    checkRestartWindow = false; // disable other window
                    checkRestartGame = false;
                    checkCloseWindow = false;
                }
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("CREDITS", ImVec2(button_width, button_height))) {
                playMenuClick();
                menu_inprogress = true;
                ae.mLevelManager->loadLevel(ED_LEVELS);
                ae.mIsPaused = false;
            }
            ImGui::SetCursorPosX(p.x - (button_width / 2));
            if (ImGui::Button("QUIT GAME", ImVec2(button_width, button_height)))
            {
                playMenuClick();
                checkRestartWindow = false; // disable other window
                checkRestartGame = false;
                checkExitToMainMenu = false;
                checkCloseWindow = true;
            }
        }

    }
    ImGui::End();
}




void UIManager::showCheckCloseWindow(){
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 175, 30));
    ImGui::SetNextWindowSize(ImVec2(350, 175));
    ImGui::Begin("CLOSE WINDOW", &checkCloseWindow, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImVec2 p;
    p.x = ImGui::GetWindowWidth() / 2;
    int button_width = ImGui::GetWindowWidth();
    int button_height = 40;
    ImGui::Text("ARE YOU SURE YOU WANT TO QUIT THE GAME ?");
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("YES", ImVec2(button_width, button_height))) ae.mIsRunning = false;
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("NO", ImVec2(button_width, button_height))) checkCloseWindow = false;
    ImGui::End();
}



void UIManager::showCheckRestartWindow(){
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 271, 30));
    ImGui::SetNextWindowSize(ImVec2(542, 175));
    ImGui::Begin("RESTART", &checkRestartWindow, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize

        );
    ImVec2 p;
    p.x = ImGui::GetWindowWidth() / 2;
    int button_width = ImGui::GetWindowWidth();
    int button_height = 40;
    ImGui::Text("ARE YOU SURE YOU WANT TO RESTART THE LEVEL ? ALL PROGRESS WILL BE LOST.");
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("YES", ImVec2(button_width, button_height)))
    {
        ae.mLevelManager->restartCurrentLevel();
        checkRestartWindow = false;
        ae.mIsPaused = false;   // close the menu
    }
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("NO", ImVec2(button_width, button_height))) checkRestartWindow = false;

    ImGui::End();
}

void UIManager::showCheckRestartGame(){
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 175, 30));
    ImGui::SetNextWindowSize(ImVec2(350, 175));
    ImGui::Begin("RESTART GAME", &checkRestartGame, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );
    ImVec2 p;
    p.x = ImGui::GetWindowWidth() / 2;
    int button_width = ImGui::GetWindowWidth();
    int button_height = 40;
    ImGui::Text("DO YOU WANT TO RESTART THE GAME ?");
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("YES", ImVec2(button_width, button_height)))
    {
        ae.mLevelManager->restartWholeGame();
        checkRestartGame = false;
        ae.mIsPaused = false;   // close the menu
    }
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("NO", ImVec2(button_width, button_height))) checkRestartGame = false;

    ImGui::End();
}

void UIManager::showCheckExitToMainMenuWindow(){
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 271, 30));
    ImGui::SetNextWindowSize(ImVec2(542, 175));
    ImGui::Begin("EXIT TO MAIN MENU", &checkRestartGame,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );
    ImVec2 p;
    p.x = ImGui::GetWindowWidth() / 2;
    int button_width = ImGui::GetWindowWidth();
    int button_height = 40;
    ImGui::Text("ARE YOU SURE YOU WANT TO EXIT TO MAIN MENU ? ALL PROGRESS WILL BE LOST.");
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("YES", ImVec2(button_width, button_height))) {
        ae.mIsPaused = false;
        menu_start = true;
        checkExitToMainMenu = false;
        ae.mLevelManager->level = COUNT_INTROS - 2;
        ae.mLevelManager->loadNextLevel();
    }
    ImGui::SetCursorPosX(p.x - (button_width / 2));
    if (ImGui::Button("NO", ImVec2(button_width, button_height))) {
        checkExitToMainMenu = false;
    }
    ImGui::End();
}
