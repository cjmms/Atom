#pragma once

//#include "Pch.hpp"
#include "GLFW/glfw3.h"
#include "utils/Serde.hpp"


class ControllerComponent {
public:
    int UP = GLFW_KEY_UP;
    int DOWN = GLFW_KEY_DOWN;
    int LEFT = GLFW_KEY_LEFT;
    int RIGHT = GLFW_KEY_RIGHT;
    int ACTION01 = GLFW_KEY_Z;
    int ACTION02 = GLFW_KEY_X;
    int ROTLEFT = GLFW_KEY_C;
    int ROTRIGHT = GLFW_KEY_V;
    glm::vec3 STEP;
    string SPEAK;
};

void controllerReact();

// CONTROLLER COMPONENT SERDE
inline void to_json(ordered_json& j, const ControllerComponent& x) {
    to_json(j["UP"], x.UP);
    to_json(j["DOWN"], x.DOWN);
    to_json(j["LEFT"], x.LEFT);
    to_json(j["RIGHT"], x.RIGHT);
    to_json(j["ACTION01"], x.ACTION01);
    to_json(j["ACTION02"], x.ACTION02);
    to_json(j["ROTLEFT"], x.ROTLEFT);
    to_json(j["ROTRIGHT"], x.ROTRIGHT);
    to_json(j["STEP"], x.STEP);
    to_json(j["SPEAK"], x.SPEAK);
}

inline void from_json(const ordered_json& j, ControllerComponent& x) {
    from_json(j["UP"], x.UP);
    from_json(j["DOWN"], x.DOWN);
    from_json(j["LEFT"], x.LEFT);
    from_json(j["RIGHT"], x.RIGHT);
    from_json(j["ACTION01"], x.ACTION01);
    from_json(j["ACTION02"], x.ACTION02);
    from_json(j["ROTLEFT"], x.ROTLEFT);
    from_json(j["ROTRIGHT"], x.ROTRIGHT);
    from_json(j["STEP"], x.STEP);
    from_json(j["SPEAK"], x.SPEAK);
}