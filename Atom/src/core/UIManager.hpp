#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"
#include "core/Event.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

// overloading less than operator 
template <>
struct std::less<std::function<void()>> {
    bool operator()(std::function<void()> const& a, std::function<void()> const& b) const {
        return a.target<void()>() < b.target<void()>();
    }
};

class UIManager {
public:
    UIManager() {

    }
    ~UIManager() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void init(GLFWwindow* window) {
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

    void addUIPainter(std::function<void()> const& uiPainter) {
        mUIPainters.insert(uiPainter);
    }

    void removeUIPainter(std::function<void()> const& uiPainter) {
        mUIPainters.erase(uiPainter);
    }

	void update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto uiPainter : mUIPainters) {
            uiPainter();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
    void onEvent(Event& e) {

    }

private:

    std::set<std::function<void()>> mUIPainters;
};

#endif