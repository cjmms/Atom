
#include <Pch.hpp>
#include "UIManager.hpp"
#include "AtomEngine.hpp"


extern AtomEngine ae;

extern ChannelID musicChannelID;
extern ChannelID sfxChannelID;
extern ChannelID dialogueChannelID;
extern float musicVolumedB;
extern float sfxVolumedB;
extern float dialogueVolumedB;
extern float listenerOffset[];
extern bool menu_start;


void UIManager::init(GLFWwindow* window) {
    const char* glsl_version = "#version 430";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
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

        showMenu();
        // check if the player wants to end the game
        if (checkCloseWindow) showCheckCloseWindow();

        // check if the player wants to restart the menu
        if (checkRestartWindow) showCheckRestartWindow();

        if (checkRestartGame) showCheckRestartGame();

    }
    else {
        for (auto& painter : mUIPainters) {
            painter();
        }
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
    //render your GUI
    ImGui::Begin("MENU", 0, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );

    if (ImGui::Button("RESUME GAME", ImVec2(ImGui::GetWindowWidth(), 40)))
    {
        checkRestartWindow = false;  // disable other window
        checkRestartGame = false;
        checkCloseWindow = false;    // disable other window
        ae.mIsPaused = false;
    }

    // Audio UI setup
    ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat("SFX VOLUME", &sfxVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat("SPEECH VOLUME", &dialogueVolumedB, 0.0f, 1.0f);

    ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

    ae.setVolume(musicChannelID, musicVolumedB);
    ae.setVolume(sfxChannelID, sfxVolumedB);
    ae.setVolume(dialogueChannelID, dialogueVolumedB);
    ae.listener3DSetXOffset(listenerOffset[0]);
    ae.listener3DSetYOffset(listenerOffset[1]);

    if (ImGui::Button("RESTART CURRENT LEVEL",ImVec2(ImGui::GetWindowWidth(),40)))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartGame = false;
        checkRestartWindow = true;
    }

    if (ImGui::Button("RESTART GAME", ImVec2(ImGui::GetWindowWidth(), 40)))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartWindow = false;
        checkRestartGame = true;
    }

    if (ImGui::Button("QUIT GAME", ImVec2(ImGui::GetWindowWidth(), 40)))
    {
        checkRestartWindow = false; // disable other window
        checkRestartGame = false;
        checkCloseWindow = true;
    }

    if (ImGui::Button("EXIT TO MAIN MENU", ImVec2(ImGui::GetWindowWidth(), 40))) {

        ae.mLevelManager->loadLevel(COUNT_INTROS - 1);
        menu_start = true;
        ae.mIsPaused = false;
    }

    ImGui::End();
}




void UIManager::showCheckCloseWindow(){
    ImGui::Begin("CLOSE WINDOW", &checkCloseWindow, 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoTitleBar |
        //ImGuiWindowFlags_NoInputs | 
        //ImGuiWindowFlags_NoScrollbar |
        //ImGuiWindowFlags_AlwaysAutoResize
        ImGuiWindowFlags_NoResize
    );   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("ARE YOU SURE YOU WANT TO QUIT THE GAME ?");

    if (ImGui::Button("YES")) ae.mIsRunning = false;
    if (ImGui::Button("NO")) checkCloseWindow = false;
    ImGui::End();
}



void UIManager::showCheckRestartWindow(){
    ImGui::Begin("RESTART", &checkRestartWindow, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("ARE YOU SURE YOU WANT TO RESTART THE LEVEL ? CURRENT PROGRESS WILL BE LOST.");
    if (ImGui::Button("YES"))
    {
        ae.mLevelManager->restartCurrentLevel();
        checkRestartWindow = false;
        ae.mIsPaused = false;   // close the menu
    }
    if (ImGui::Button("NO")) checkRestartWindow = false;

    ImGui::End();
}

void UIManager::showCheckRestartGame(){
    ImGui::Begin("RESTART GAME", &checkRestartGame, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("DO YOU WANT TO RESTART THE GAME?");
    if (ImGui::Button("YES"))
    {
        ae.mLevelManager->restartWholeGame();
        checkRestartGame = false;
        ae.mIsPaused = false;   // close the menu
    }
    if (ImGui::Button("NO")) checkRestartGame = false;

    ImGui::End();
}
