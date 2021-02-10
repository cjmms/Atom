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

void demoSetup()
{
   // EntityID rectangle = ae.createEntity();
   // 
   // ae.addComponent(rectangle, RectangleComponent{
   //     glm::vec3{1,1,1},   //colors
   //     false
   //     });
   // ae.addComponent(rectangle, TransformComponent{
   //     glm::vec3{0, -1, 0}, // position
   //     glm::vec3{0.0f,0.0f,0.0f}, // rotation
   //     glm::vec3{1,1,1.0f},  // scale 
   //     glm::mat4(1.0f)
   //     });
   // ae.addComponent(rectangle, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   // ae.addComponent(rectangle, PhysicsBodyComponent(1, true));

   // EntityID rectangle2 = ae.createEntity();

   // ae.addComponent(rectangle2, RectangleComponent{
   //     glm::vec3{1,1,1},   //colors
   //     false
   //     });
   // ae.addComponent(rectangle2, TransformComponent{
   //     glm::vec3{1, 0, 0}, // position
   //     glm::vec3{0.0f,0.0f,0.0f}, // rotation
   //     glm::vec3{1,1,1.0f},  // scale 
   //     glm::mat4(1.0f)
   //     });
   // ae.addComponent(rectangle2, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   // ae.addComponent(rectangle2, PhysicsBodyComponent(1, true));

   // EntityID rectangle3 = ae.createEntity();

   // ae.addComponent(rectangle3, RectangleComponent{
   //     glm::vec3{0.5f,0.5f,0.5f},
   //     false
   //     });

   // ae.addComponent(rectangle3, TransformComponent{
   //     glm::vec3{0, -0.1, 0}, // position
   //     glm::vec3{0.0f,0.0f,0.0f}, // rotation
   //     glm::vec3{0.1f,0.1f,0.1f},  // scale 
   //     glm::mat4(1.0f)
   //     });
   // ae.addComponent(rectangle3, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   // ae.addComponent(rectangle3, PhysicsBodyComponent(1, false));
   // ae.addComponent(rectangle3, ControllerComponent());

   // EntityID rectangle4 = ae.createEntity();

   // ae.addComponent(rectangle4, RectangleComponent{
   //     glm::vec3{1,1,1},   //colors
   //     false
   //     });
   // ae.addComponent(rectangle4, TransformComponent{
   //     glm::vec3{-1, 0, 0}, // position
   //     glm::vec3{0.0f,0.0f,0.0f}, // rotation
   //     glm::vec3{1,1,1.0f},  // scale 
   //     glm::mat4(1.0f)
   //     });
   // ae.addComponent(rectangle4, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   // ae.addComponent(rectangle4, PhysicsBodyComponent(1, true));


   //EntityID rectangle5 = ae.createEntity();
   //
   //ae.addComponent(rectangle5, RectangleComponent{
   //    glm::vec3{1,1,1},   //colors
   //    false
   //    });
   //ae.addComponent(rectangle5, TransformComponent{
   //    glm::vec3{0, 1, 0}, // position
   //    glm::vec3{0.0f,0.0f,0.0f}, // rotation
   //    glm::vec3{0.8f,0.8f,0.8f},  // scale 
   //    glm::mat4(1.0f)
   //    });
   //ae.addComponent(rectangle5, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   //ae.addComponent(rectangle5, PhysicsBodyComponent(1, true));

   //ae.save("level_01.json");
   ae.load("level_01.json");
}


void initSpectrum() {
    for (int i = 0; i < 200; ++i) {
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
        ae.addComponent(rectangle, ShapeComponent{ ShapeComponent::ShapeType::AABB });
        ae.addComponent(rectangle, PhysicsBodyComponent(1, true));
    }
}

void audioReact() {
    auto fftbars = ae.mAudioManager->fft();
    for (int i = 0; i < 100;++i) {
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

void volumeController(ChannelID channelid) {
    if (ae.mInputManager->isKeyTriggered(VK_OEM_PLUS)) {
        float currentvol = ae.mAudioManager->getChannelVolumedB(channelid);
        ae.mAudioManager->setChannelVolumedB(channelid, std::clamp(currentvol + DB_STEP,0.0f,1.0f));
        ATOM_INFO("VOLUME dB : {}", ae.mAudioManager->getChannelVolumedB(channelid));

    }
    if (ae.mInputManager->isKeyTriggered(VK_OEM_MINUS)) {
        float currentvol = ae.mAudioManager->getChannelVolumedB(channelid);
        ae.mAudioManager->setChannelVolumedB(channelid, std::clamp(currentvol - DB_STEP, 0.0f, 1.0f));
        ATOM_INFO("VOLUME dB : {}", ae.mAudioManager->getChannelVolumedB(channelid));
    }
}


int main(int argc, char** argv){

    console();      // setup the console 
    Log::init();    // setup logging
    
    ae.init();          // initialize engine
    ae.setMaxFPS(60);  // set the fps

    ae.printGraphicsInfo(); // print OpenGL info
    
    // register all components 
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
        ae.setSystemArchetype<ControllerSystem>(typeController);
    }
    
    // need to initialize systems again because systems got updated above
    ae.initSystem();
    string musicTrack = "Atom/res/wariyo_mortals.ogg";
    ae.loadSound(musicTrack);

    ChannelID musicChannelID = ae.play(musicTrack, ChannelGroupTypes::C_MUSIC, 0.2f);
    //demoSetup();

    initSpectrum();
	
    // game loop
    while (ae.mIsRunning) {
        glfwpoll();
        ae.update();
        volumeController(musicChannelID);
        audioReact();
        //makeSingleRectangle();
        fpsCounter();
    }

    return 0;
}