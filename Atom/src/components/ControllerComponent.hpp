/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ControllerComponent.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Defines Controls for an entity
* @date		2021-02-03
*/

#pragma once

//#include "Pch.hpp"
#include "GLFW/glfw3.h"
#include "utils/Serde.hpp"
#include "core/Types.hpp"
#include "utils/AtomKeycode.hpp"


class ControllerComponent {
public:
    AtomKeycode UP;
    AtomKeycode DOWN;
    AtomKeycode LEFT;
    AtomKeycode RIGHT;
    AtomKeycode SWAP_POSITION;
    AtomKeycode SWAP_CHARACTER;
    AtomKeycode GOD_MODE;
    AtomKeycode SUPER_GOD_MODE;
    AtomKeycode NEXT_LEVEL;
    AtomKeycode PREV_LEVEL;
    AtomKeycode ED_LEVEL;
    AtomKeycode FINAL_LEVEL;
    AtomKeycode IDIE;
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
    to_json(j["GOD_MODE"], x.GOD_MODE);
    to_json(j["SUPER_GOD_MODE"], x.SUPER_GOD_MODE);
    to_json(j["NEXT_LEVEL"], x.NEXT_LEVEL);
    to_json(j["PREV_LEVEL"], x.PREV_LEVEL);
    to_json(j["ED_LEVEL"], x.ED_LEVEL);
    to_json(j["FINAL_LEVEL"], x.FINAL_LEVEL);
    to_json(j["IDIE"], x.IDIE);
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
    from_json(j["GOD_MODE"], x.GOD_MODE);
    from_json(j["SUPER_GOD_MODE"], x.SUPER_GOD_MODE);
    from_json(j["NEXT_LEVEL"], x.NEXT_LEVEL);
    from_json(j["PREV_LEVEL"], x.PREV_LEVEL);
    from_json(j["ED_LEVEL"], x.ED_LEVEL);
    from_json(j["FINAL_LEVEL"], x.FINAL_LEVEL);
    from_json(j["IDIE"], x.IDIE);
    from_json(j["ROTLEFT"], x.ROTLEFT);
    from_json(j["ROTRIGHT"], x.ROTRIGHT);

    from_json(j["isActive"], x.isActive);

}