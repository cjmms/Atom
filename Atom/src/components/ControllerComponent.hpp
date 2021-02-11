#pragma once

//#include "Pch.hpp"
#include "GLFW/glfw3.h"
#include "utils/Serde.hpp"
#include "core/Types.hpp"
#include "utils/AtomScancode.hpp"


class ControllerComponent {
public:
    AtomScancode UP;
    AtomScancode DOWN;
    AtomScancode LEFT;
    AtomScancode RIGHT;
    AtomScancode SWAP_POSITION;
    AtomScancode SWAP_CHARACTER;
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