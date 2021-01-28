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
        false
    });

    ae.addComponent(rectangle, TransformComponent{
        glm::vec3{(random() * 2.0f) - 1.0f,(random() * 2.0f) - 1.0f, 0.0f}, // position
        glm::vec3{0.0f,0.0f,0.0f}, // rotation
        glm::vec3{random(),random(),1.0f},  // scale 
        glm::mat4(1.0f)
    });

    return rectangle;

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
    ae.setMaxFPS(120);  // set the fps

    ae.printGraphicsInfo(); // print OpenGL info
    
    // register all components 
    ae.registerComponent<RectangleComponent>();
    ae.registerComponent<TransformComponent>();

    // register all systems
    ae.registerSystem<RectangleRenderSystem>();

    // set archetypes
    {
        Archetype atype;        // this is a bitset denoting the system archetye
        atype.set(ae.getComponentType<RectangleComponent>());
        atype.set(ae.getComponentType<TransformComponent>());
        ae.setSystemArchetype<RectangleRenderSystem>(atype);
    }
    
    // need to initialize systems again because systems got updated above
    ae.initSystem();

    // game loop
    while (ae.mIsRunning) {
        glfwpoll();
        ae.update();
        makeSingleRectangle();
        fpsCounter();
    }

    return 0;
}