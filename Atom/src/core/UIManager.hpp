/*
* @file		UIManager.hpp
* @author	Abhikalp Unakal
* @brief	UI Orchestrator
* @date		2021-04-09
*/

#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include "Pch.hpp"
#include "core/Event.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//// overloading less than operator 
//template <>
//struct std::less<std::function<void()>> {
//    bool operator()(std::function<void()> const& a, std::function<void()> const& b) const {
//        return a.target<void()>() < b.target<void()>();
//    }
//};

//    // overloading equals operator 
//bool operator==(std::function<void()>& a, std::function<void()>& b) {
//    return a.target<void()>() == b.target<void()>();
//}
//
//// overloading less than operator 
//bool operator<(std::function<void()>& a, std::function<void()>& b) {
//    return a.target<void()>() < b.target<void()>();
//}

class UIManager {
public:
    ~UIManager();       
    void init(GLFWwindow* window); 
    void update(); 
    void onEvent(Event& e) {}
    void closeWindow();
    void drawText(int x, int y, const char* string);
    void addUIPainter(const std::function<void()> const& uiPainter);
    void removeUIPainter(const std::function<void()> const& uiPainter);



//private:
    void showMenu();
    void showCheckCloseWindow();
    void showCheckRestartWindow();
    void showCheckRestartGame();

//public:
    bool checkRestartGame = false;

    //// overloading equals operator 
    //friend bool operator==(std::function<void()>& a, std::function<void()>& b) {
    //    return a.target<void()>() == b.target<void()>();
    //}

    //// overloading less than operator 
    //friend bool operator<(std::function<void()>& a, std::function<void()>& b) {
    //    return a.target<void()>() < b.target<void()>();
    //}

    struct comparator {
    public:
        bool operator()(const std::function<void()> const& a, const std::function<void()> const& b) const {
            auto v1 = &a;
            auto v2 = &b;
            return v1 < v2;
        }
    };

//private:
    bool checkCloseWindow = false;
    bool checkRestartWindow = false;
    std::set<std::function<void()>,comparator> mUIPainters;
    
};

#endif