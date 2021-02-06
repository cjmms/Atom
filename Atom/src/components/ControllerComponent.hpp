#pragma once

//#include "Pch.hpp"
#include "GLFW/glfw3.h"
#include "utils/Serde.hpp"

#define VK_Z    0x5A
#define VK_X    0x58


class ControllerComponent {
public:
    int UP = VK_UP;
    int DOWN = VK_DOWN;
    int LEFT = VK_LEFT;
    int RIGHT = VK_RIGHT;
    int SWAP_POSITION = VK_Z;
    int SWAP_CHARACTER = VK_X;
    int ROTLEFT = GLFW_KEY_C;
    int ROTRIGHT = GLFW_KEY_V;

    bool isActive = TRUE;
};

// CONTROLLER COMPONENT SERDE
inline void to_json(ordered_json& j, const ControllerComponent& x) {
    to_json(j["UP"], x.UP);
    to_json(j["DOWN"], x.DOWN);
    to_json(j["LEFT"], x.LEFT);
    to_json(j["RIGHT"], x.RIGHT);
    to_json(j["SWAP_POSITION"], x.SWAP_POSITION);
    to_json(j["SWAP_CHARACTER"], x.SWAP_CHARACTER);
    to_json(j["ROTLEFT"], x.ROTLEFT);
    to_json(j["ROTRIGHT"], x.ROTRIGHT);
    
    to_json(j["isActive"], x.isActive);
}

inline void from_json(const ordered_json& j, ControllerComponent& x) {
    from_json(j["UP"], x.UP);
    from_json(j["DOWN"], x.DOWN);
    from_json(j["LEFT"], x.LEFT);
    from_json(j["RIGHT"], x.RIGHT);
    from_json(j["SWAP_POSITION"], x.SWAP_POSITION);
    from_json(j["SWAP_CHARACTER"], x.SWAP_CHARACTER);
    from_json(j["ROTLEFT"], x.ROTLEFT);
    from_json(j["ROTRIGHT"], x.ROTRIGHT);

    from_json(j["isActive"], x.isActive);

}