/*
* @file		Application.cpp
* @author	Abhikalp Unakal
* @brief	main bootstrapper
* @date		2021-01-12
*/

#include <Pch.hpp>
#include <cstdlib>
#include <clocale>

#include "core/Types.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"

// THE ENGINE
AtomEngine ae;

// all compoennts 
#include "components/AllComponents.hpp"
#include "systems/RectangleRenderSystem.hpp"
#include "systems/PhysicsSystem.hpp"
#include "systems/ControllerSystem.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

// max 80 to prevent using new and having memory leaks 
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

void fpsCounter() {
    char title[MAX_TITLE_LEN];
    snprintf(title, MAX_TITLE_LEN, "[ATOM] FPS: %f", ae.mChrononManager->getFPS());
#ifdef _WIN64
    setConsoleTitle(title);
#else
    std::cout << "[ATOM] FPS: " << ae.mChrononManager->getFPS() << std::endl;
#endif
}

float random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
    return (float)dis(gen);
}


EntityID makeSingleRectangle() {

    EntityID rectangle = ae.createEntity();

    ae.addComponent(rectangle, RectangleComponent{
        glm::vec3{random(),random(),random()},
        false, 
        "Atom/res/img.jpg"
    });

    ae.addComponent(rectangle, TransformComponent{
        glm::vec3{(random() * 2.0f) - 1.0f,(random() * 2.0f) - 1.0f, 0.0f}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{random(),random(),1.0f},  // scale 
        glm::mat4(1.0f)
    });

    return rectangle;
}

void audioReact() {
    auto fftbars = ae.mAudioManager->fft();
    for (int i = 0; i < 200;++i) {
        TransformComponent& rt = ae.getComponent<TransformComponent>((EntityID)i);
        rt.scale.y = fftbars->spectrum[0][i] * 10.0f;
    }
}

#define VK_MINUS 0x0C
#define VK_PLUS 0x0D
#define DB_STEP 0.02f

void glfwpoll() {
    glfwPollEvents();
    if (ae.mGraphicsManager->shouldWindowClose()) {
        ae.mIsRunning = false;
    }

}

string musicTrack = "Atom/res/wariyo_mortals.ogg";
string sfxTrack = "Atom/res/optimus_speech.ogg";
ChannelID musicChannelID = -1;
ChannelID sfxChannelID = -1;


float getVolumedB(ChannelID channelid) {
    return ae.mAudioManager->getChannelVolumedB(channelid);
}

void setVolume(ChannelID channelid, float volumedB) {
    ae.mAudioManager->setChannelVolumedB(channelid, std::clamp(volumedB, 0.0f, 1.0f));
}

FMOD_VECTOR camera_position{0.0f,0.0f,0.0f};
FMOD_VECTOR camera_fwd{0.0f,0.0f,1.0f};
FMOD_VECTOR camera_up{0.0f,1.0f,0.0f};
float camera_step = 0.1f;

void listener3DSetXOffset(float offset) {
    camera_position.x = 0.0f + offset;
    ae.mAudioManager->mCoreSystem->set3DListenerAttributes(0, &camera_position, 0, &camera_fwd, &camera_up);
}

void listener3DSetYOffset(float offset) {
    camera_position.y = 0.0f + offset;
    ae.mAudioManager->mCoreSystem->set3DListenerAttributes(0, &camera_position, 0, &camera_fwd, &camera_up);
}

int main(int argc, char** argv){

    console();      // setup the console 
    Log::init();    // setup logging
    
    ae.init();          // initialize engine
    ae.setMaxFPS(60);  // set the fps

    // IMGUI GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    ae.printGraphicsInfo(); // print OpenGL info
    
    // register all components 
    ae.registerComponent<TagComponent>();
    ae.registerComponent<RectangleComponent>();
    ae.registerComponent<TransformComponent>();
    ae.registerComponent<PhysicsBodyComponent>();
    ae.registerComponent<ShapeComponent>();
    ae.registerComponent<ControllerComponent>();

    // register all systems
    ae.registerSystem<RectangleRenderSystem>();
    ae.registerSystem<PhysicsSystem>();
    ae.registerSystem<ControllerSystem>();
	

    // set archetypes
    {
        Archetype typeRectangleRender;        // this is a bitset denoting the system archetye
        typeRectangleRender.set(ae.getComponentType<RectangleComponent>());
        typeRectangleRender.set(ae.getComponentType<TransformComponent>());
        ae.setSystemArchetype<RectangleRenderSystem>(typeRectangleRender);

        Archetype typePhysics;
        typePhysics.set(ae.getComponentType<TransformComponent>());
        typePhysics.set(ae.getComponentType<PhysicsBodyComponent>());
        typePhysics.set(ae.getComponentType<ShapeComponent>());
        ae.setSystemArchetype<PhysicsSystem>(typePhysics);

        Archetype typeController;
        typeController.set(ae.getComponentType<ControllerComponent>());
        typeController.set(ae.getComponentType<PhysicsBodyComponent>());
        typeController.set(ae.getComponentType<TransformComponent>());
        ae.setSystemArchetype<ControllerSystem>(typeController);
    }
    
    // need to initialize systems again because systems got updated above
    ae.initSystem();

    ae.loadSound(musicTrack);
    ae.loadSound(sfxTrack);
    
    ae.load("level_01.json");

    musicChannelID = ae.play(musicTrack, ChannelGroupTypes::C_MUSIC, 0.01f);
    sfxChannelID = ae.play(sfxTrack, ChannelGroupTypes::C_SFX, 0.1f);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(ae.mGraphicsManager->getWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // game loop
    while (ae.mIsRunning) {
        glfwpoll();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ae.update();

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // render your GUI
        ImGui::Begin("ATOM AUDIO CONTROL PANEL");
        static float musicVolumedB = 0.05f;
        static float sfxVolumedB = 0.1f; 
        static float listenerXOffset = 0.0f;
        static float listenerYOffset = 0.0f;
        static float listenerOffset[] = { 0.0f,0.0f };

        ImGui::SliderFloat("MUSIC VOLUME", &musicVolumedB, 0.0f, 1.0f);
        ImGui::SliderFloat("SPEECH VOLUME", &sfxVolumedB, 0.0f, 1.0f);

        setVolume(musicChannelID, musicVolumedB);
        setVolume(sfxChannelID, sfxVolumedB);

        ImGui::SliderFloat2("LISTENER", listenerOffset, -10.0, 10.0);

        listener3DSetXOffset(listenerOffset[0]);
        listener3DSetYOffset(listenerOffset[1]);

        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        int display_w, display_h;
        glfwGetFramebufferSize(ae.mGraphicsManager->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(ae.mGraphicsManager->getWindow());

        audioReact();
        //makeSingleRectangle();
        fpsCounter();
    }

    ae.save("level_01.json");
    return 0;
}