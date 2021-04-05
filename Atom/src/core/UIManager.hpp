#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include "Pch.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Event;


// overloading less than operator 
template <>
struct std::less<std::function<void()>> {
    bool operator()(std::function<void()> const& a, std::function<void()> const& b) const {
        return a.target<void()>() < b.target<void()>();
    }
};

class UIManager {
public:
    ~UIManager();       

    void init(GLFWwindow* window); 


    void update(); 


    void onEvent(Event& e) {}

private:
    bool checkCloseWindow = false;
    bool checkRestartWindow = false;


    void showMenu();
    void showCheckCloseWindow();
    void showCheckRestartWindow();

};

#endif