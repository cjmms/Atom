/*
* @file		Application.cpp
* @author	Team Atom
* @brief	main bootstrapper
* @date		2021-01-12
*/

#include <Pch.hpp>
#include <cstdlib>
#include <clocale>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "src/core/Renderer.hpp"
//#define GLEW_STATIC

#include "components/Body.hpp"
#include "core/Types.hpp"
#include "utils/Log.hpp"
#include "components/RenderBoxComponent.hpp"
#include "components/Transform.hpp"
#include "core/FrameRateController.hpp"
#include "core/PhysicsManager.hpp"

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

//allocating console
void console() {
#ifdef _WIN64
    if (AllocConsole())
    {
        FILE* file;

        freopen_s(&file, "CONOUT$", "wt", stdout);
        freopen_s(&file, "CONOUT$", "wt", stderr);
        freopen_s(&file, "CONOUT$", "wt", stdin);

        SetConsoleTitle(L"[Lime]");
    }
#endif
}

// max 80 to prevent using new and having memory leaks 
void setConsoleTitle(const char* title) {
    std::setlocale(LC_ALL, "en_US.utf8");
    std::wcout.imbue(std::locale("en_US.utf8"));
    wchar_t wstr[80];
    // +1 to account for \0 termination
    size_t wsize;
    mbstowcs_s(&wsize, wstr, strlen(title) + 1, title, strlen(title));
    SetConsoleTitle(wstr);
}
#endif

float random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
    return (float)dis(gen);
}

void serdeDemo() {

    // simple serde demo
    ATOM_INFO("Simple Serde Demo...");
    // saving to file
    RenderBoxComponent rbc01{ glm::vec3{0.0f,1.0f,1.0f} };
    ordered_json j01;
    to_json(j01, rbc01);
    save("out01.json", j01);

    // loading from file
    RenderBoxComponent rbc02;
    ordered_json j02;
    load("out01.json", j02);
    from_json(j02, rbc02);

    // log both values
    ATOM_TRACE("RenderBoxComponent 1...");
    std::cout << std::setw(4) << j01 << std::endl;
    ATOM_TRACE("RenderBoxComponent 2...");
    std::cout << std::setw(4) << j02 << std::endl;

    // advanced serde demo
    ATOM_INFO("Advanced Serde Demo...");
    // saving
    ordered_json j03 = json::array();
    for (int i = 0; i < 10;++i) {
        ordered_json j04;
        RenderBoxComponent rbc03{ glm::vec3{random(),random(),random()} };
        to_json(j04, rbc03);
        j03.push_back(j04);
    }
    save("out02.json", j03);

    //loading
    unsigned int count = 0;
    ordered_json j05 = json::array();
    std::vector<RenderBoxComponent> rbc04;
    load("out02.json", j05);
    for (auto& j06 : j05) {
        RenderBoxComponent rbc05;
        from_json(j06, rbc05);
        ATOM_TRACE("RenderBoxComponent {}", count++);
        std::cout << std::setw(4) << j06 << std::endl;
        rbc04.push_back(rbc05);
    }
    ATOM_TRACE("Vector size : {}", rbc04.size());
    ATOM_INFO("Done...")
}

int main(void)
{
    // allocating and setting up console
    // initializing logging 
    console();
    setConsoleTitle(APPNAME);
    Log::init();

    serdeDemo();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, APPNAME, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init error" << std::endl;
        return false;
    }
    
    Renderer renderer;
    FrameRateController frameRateController(60);
    PhysicsManager physicsManager;

    glm::vec2 pos(0.0, 0.0);
    glm::vec2 scale(1.0, 1.0);
    glm::vec3 color(0.2, 0.4, 0.8);
    Transform* t1 = new Transform();
    t1->positionX = 0.0;
    t1->positionY = 0.0;
    t1->scaleX = 1.0;
    t1->scaleY = 1.0;
    Body* b1 = new Body(t1);
    Shape* shape1 = new ShapeAABB(b1, t1);
    b1->shape = shape1;
    b1->Integrate(0, 0);
	
    glm::vec2 pos2(0.0, 0.5);
    glm::vec2 scale2(0.1, 0.1);
    glm::vec3 color2(1, 1, 1);
    Transform* t2 = new Transform();
    t2->positionX = 0.0;
    t2->positionY = 0.5;
    t2->scaleX = 0.1;
    t2->scaleY = 0.1;
    Body* b2 = new Body(t2);
    Shape* shape2 = new ShapeAABB(b2, t2);
    b2->shape = shape2;
    b2->Integrate(0, 0);

    //renderer.EnableFrameWireMode();
    // Test glm has been setup properly
    glm::vec3(1.0f);

	
    while (!glfwWindowShouldClose(window))
    {
        frameRateController.FrameStart();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        pos.x = t1->positionX;
        pos.y = t1->positionY;
        pos2.x = t2->positionX;
        pos2.y = t2->positionY;
    	
        scale.x = t1->scaleX;
        scale.y = t1->scaleY;
        scale2.x = t2->scaleX;
        scale2.y = t2->scaleY;

        renderer.DrawRec(pos, scale, color);
        renderer.DrawRec(pos2, scale2, color2);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        auto frameTime = frameRateController.GetFrameTime();
        physicsManager.Update(frameTime, b1, b2);
    	
        frameRateController.FrameEnd();
    }

    glfwTerminate();
    return 0;
}