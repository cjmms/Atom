/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		TagComponent.hpp
* @author	Abhikalp Unakal
* @brief	Used to tag each entity 
* @date		2021-02-10
*/

#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP
#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"
class TagComponent {
public:
    string tag;
};

// TRANSFORM COMPONENT SERDE
inline void to_json(ordered_json& j, const TagComponent& x) {
    to_json(j["tag"], x.tag);
}

inline void from_json(const ordered_json& j, TagComponent& x) {
    from_json(j["tag"], x.tag);
}

#endif