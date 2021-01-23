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

#include "core/Types.hpp"
#include "utils/Log.hpp"
#include "components/RenderBoxComponent.hpp"
#include "components/RectangleComponent.hpp"
#include "core/EventManager.hpp"


RectangleComponent rc01, rc02;
RectangleComponent rc03, rc04;

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
    ATOM_INFO("Done...");

    // removing the temp files
    remove("out01.json");
    remove("out02.json");
}

void onEvent01(Event& e) {
    if (e.getType() == EventID::E_WINDOW_KEY_PRESSED) {
        ATOM_INFO("KEYCODE : {}", e.getParam<int>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE));
    }
}

void serdeRectangles() {
    //serialize 2 rectangles

    //saving 
    //rc01.color = { glm::vec3{random(),random(),random()} };
    //rc01.position = { glm::vec2{-0.5,0.5} };
    //rc01.scale = { glm::vec2{0.1,0.1} };

    //rc02.color = { glm::vec3{random(),random(),random()} };
    //rc02.position = { glm::vec2{-0.5,-0.5} };
    //rc02.scale = { glm::vec2{0.1,0.1} };

    ////saving
    ordered_json j07 = {};
    //to_json(j07["rc01"], rc01);

    //to_json(j07["rc02"], rc02);
    //save("rectangles.json", j07);

    //loading
    ordered_json j08;
    load("rectangles.json", j08);


    from_json(j08["rc01"], rc03);
    from_json(j08["rc02"], rc04);


}


int main(void)
{
    EventManager em;
    em.addListener(EventID::E_WINDOW_KEY_PRESSED, onEvent01);

    // allocating and setting up console
    // initializing logging 
    console();
    setConsoleTitle(APPNAME);
    Log::init();


    Event e(EventID::E_WINDOW_KEY_PRESSED);
    e.setParam<int>(EventID::P_WINDOW_KEY_PRESSED_KEYCODE, 7);
    em.sendEvent(e);

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

    //glm::vec2 pos(0.0, 0.0);
    glm::vec2 pos(0.0, 0.0);
    glm::vec2 scale(1.0, 1.0);
    glm::vec3 color(0.2, 0.4, 0.8);

    // renderer.EnableFrameWireMode();
    // Test glm has been setup properly
    glm::vec3(1.0f);
    serdeRectangles();

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        renderer.DrawRec(rc03.position, rc03.scale, rc03.color);
        renderer.DrawRec(rc04.position, rc04.scale, rc04.color);

        //renderer.DrawRec(pos, scale, color);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}