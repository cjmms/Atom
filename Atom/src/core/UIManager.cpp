
#include <Pch.hpp>
#include "UIManager.hpp"
#include "AtomEngine.hpp"


extern AtomEngine ae;


extern float musicVolumedB;
extern float sfxVolumedB;
extern float dialogVolumedB;
extern float listenerOffset[];



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

void UIManager::addUIPainter(std::function<void()> const& uiPainter){
    mUIPainters.insert(uiPainter);
}

void UIManager::removeUIPainter(std::function<void()> const& uiPainter){
    mUIPainters.erase(uiPainter);
}



void UIManager::showMenu(){
    //render your GUI
    ImGui::Begin("MENU", 0, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("RESUME GAME"))
    {
        checkRestartWindow = false;  // disable other window
        checkRestartGame = false;
        checkCloseWindow = false;    // disable other window
        ae.mIsPaused = false;
    }

    // Audio UI setup
    ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat("SFX VOLUME", &sfxVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat("SPEECH VOLUME", &dialogVolumedB, 0.0f, 1.0f);

    ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

    ae.setVolume(musicChannelID, musicVolumedB);
    ae.setVolume(sfxChannelID, sfxVolumedB);
    ae.listener3DSetXOffset(listenerOffset[0]);
    ae.listener3DSetYOffset(listenerOffset[1]);

    if (ImGui::Button("RESTART CURRENT LEVEL"))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartGame = false;
        checkRestartWindow = true;
    }

    if (ImGui::Button("RESTART GAME"))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartWindow = false;
        checkRestartGame = true;
    }

    if (ImGui::Button("QUIT GAME"))
    {
        checkRestartWindow = false; // disable other window
        checkRestartGame = false;
        checkCloseWindow = true;
    }

    ImGui::End();
}




void UIManager::showCheckCloseWindow(){
    ImGui::Begin("CLOSE WINDOW", &checkCloseWindow, ImGuiWindowFlags_NoCollapse);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
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
