
#include <Pch.hpp>
#include "UIManager.hpp"
#include "AtomEngine.hpp"


extern AtomEngine ae;


extern float musicVolumedB;
extern float sfxVolumedB;
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



UIManager::~UIManager()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



void UIManager::update()
{
    // if the game is not paused, do not show menu UI
    if (!ae.mIsPaused) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    showMenu();
    
    // check if the player wants to end the game
    if (checkCloseWindow) showCheckCloseWindow();

    // check if the player wants to restart the menu
    if (checkRestartWindow) showCheckRestartWindow();
    
    if (checkRestartGame) showCheckRestartGame();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::closeWindow()
{
    ae.mIsPaused = true;
    checkCloseWindow = true;
}





void UIManager::showMenu()
{
    //render your GUI
    ImGui::Begin("Menu", 0, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Resume Game"))
    {
        checkRestartWindow = false;  // disable other window
        checkRestartGame = false;
        checkCloseWindow = false;    // disable other window
        ae.mIsPaused = false;
    }

    // Audio UI setup
    ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat("SPEECH VOLUME", &sfxVolumedB, 0.0f, 1.0f);
    ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

    ae.setVolume(musicChannelID, musicVolumedB);
    ae.setVolume(sfxChannelID, sfxVolumedB);
    ae.listener3DSetXOffset(listenerOffset[0]);
    ae.listener3DSetYOffset(listenerOffset[1]);

    if (ImGui::Button("Restart Current Level"))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartGame = false;
        checkRestartWindow = true;
    }

    if (ImGui::Button("Restart Game"))
    {
        checkCloseWindow = false;   // disable other window
        checkRestartWindow = false;
        checkRestartGame = true;
    }

    if (ImGui::Button("Quit Game"))
    {
        checkRestartWindow = false; // disable other window
        checkRestartGame = false;
        checkCloseWindow = true;
    }

    ImGui::End();
}




void UIManager::showCheckCloseWindow()
{
    ImGui::Begin("CloseWindow", &checkCloseWindow, ImGuiWindowFlags_NoCollapse);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Are you sure you want to quit the game?");

    if (ImGui::Button("Yes")) ae.mIsRunning = false;
    if (ImGui::Button("No")) checkCloseWindow = false;
    ImGui::End();
}



void UIManager::showCheckRestartWindow()
{
    ImGui::Begin("Restart", &checkRestartWindow, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Are you sure you want to restart the level? Current progress will lost.");
    if (ImGui::Button("Yes"))
    {
        ae.mLevelManager->restartCurrentLevel();
        checkRestartWindow = false;
        ae.mIsPaused = false;   // close the menu
    }
    if (ImGui::Button("No")) checkRestartWindow = false;

    ImGui::End();
}

void UIManager::showCheckRestartGame()
{
    ImGui::Begin("Restart Game", &checkRestartGame, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Do you want to restart the game?");
    if (ImGui::Button("Yes"))
    {
        ae.mLevelManager->restartWholeGame();
        checkRestartGame = false;
        ae.mIsPaused = false;   // close the menu
    }
    if (ImGui::Button("No")) checkRestartGame = false;

    ImGui::End();
}
