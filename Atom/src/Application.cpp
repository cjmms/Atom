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
    EntityID floor = ae.createEntity();
    ae.addComponent(floor, RectangleComponent{
        glm::vec3{1,1,1},   //colors
        false
        });
    ae.addComponent(floor, TransformComponent{
        glm::vec3{0, -1, 0}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{10,1,1.0f},  // scale 
        glm::mat4(1.0f)
        });
    ae.addComponent(floor, ShapeComponent{ ShapeComponent::ShapeType::AABB });
    ae.addComponent(floor, PhysicsBodyComponent(1, true));

    EntityID wall1 = ae.createEntity();
    ae.addComponent(wall1, RectangleComponent{
        glm::vec3{1,1,1},   //colors
        false
        });
    ae.addComponent(wall1, TransformComponent{
        glm::vec3{1, 0, 0}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{1,1,1.0f},  // scale 
        glm::mat4(1.0f)
        });
    ae.addComponent(wall1, ShapeComponent{ ShapeComponent::ShapeType::AABB });
    ae.addComponent(wall1, PhysicsBodyComponent(1, true));

	//large
    EntityID player1 = ae.createEntity();
    ae.addComponent(player1, RectangleComponent{
        glm::vec3{0.5f,0.5f,0.5f},
        false
        });
    ae.addComponent(player1, TransformComponent{
        glm::vec3{0, -0.1, 0}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{0.3f,0.2f,0.0f},  // scale 
        glm::mat4(1.0f)
        });
    ae.addComponent(player1, ShapeComponent{ ShapeComponent::ShapeType::AABB });
    ae.addComponent(player1, PhysicsBodyComponent(2, false));
    auto& controller1 = ControllerComponent();
	controller1.isActive = true;
    ae.addComponent(player1, controller1);

	//small
    EntityID player2 = ae.createEntity();
    ae.addComponent(player2, RectangleComponent{
        glm::vec3{0.8f,0.8f,0.5f},
        false
        });
    ae.addComponent(player2, TransformComponent{
        glm::vec3{0, -0.1, 0}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{0.1f,0.1f,0.1f},  // scale 
        glm::mat4(1.0f)
        });
    ae.addComponent(player2, ShapeComponent{ ShapeComponent::ShapeType::AABB });
    ae.addComponent(player2, PhysicsBodyComponent(1, false));
    auto& controller2 = ControllerComponent();
	controller2.isActive = false;
    ae.addComponent(player2, controller2);
    

    //EntityID leftwall = ae.createEntity();
    //ae.addComponent(leftwall, RectangleComponent{
    //    glm::vec3{1,1,1},   //colors
    //    false
    //    });
    //ae.addComponent(leftwall, TransformComponent{
    //    glm::vec3{-1, 0, 0}, // position
    //    glm::vec3{0.0f,0.0f,0.0f}, // rotation
    //    glm::vec3{1,1,1.0f},  // scale 
    //    glm::mat4(1.0f)
    //    });
    //ae.addComponent(leftwall, ShapeComponent{ ShapeComponent::ShapeType::AABB });
    //ae.addComponent(leftwall, PhysicsBodyComponent(1, true));


   EntityID wallceiling = ae.createEntity();
   ae.addComponent(wallceiling, RectangleComponent{
       glm::vec3{1,1,1},   //colors
       false
       });
   ae.addComponent(wallceiling, TransformComponent{
       glm::vec3{0, 1, 0}, // position
       glm::vec3{0.0f,0.0f,0.0f}, // rotation
       glm::vec3{0.8f,0.8f,0.8f},  // scale 
       glm::mat4(1.0f)
       });
   ae.addComponent(wallceiling, ShapeComponent{ ShapeComponent::ShapeType::AABB });
   ae.addComponent(wallceiling, PhysicsBodyComponent(1, true));

}

void glfwpoll() {
    glfwPollEvents();
    if (ae.mGraphicsManager->shouldWindowClose()) {
        ae.mIsRunning = false;
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
        typeController.set(ae.getComponentType<TransformComponent>());
        ae.setSystemArchetype<ControllerSystem>(typeController);
    }
    
    // need to initialize systems again because systems got updated above
    ae.initSystem();

    demoSetup();
	
    // game loop
    while (ae.mIsRunning) {
        glfwpoll();
        ae.update();
        fpsCounter();
    }

    return 0;
}