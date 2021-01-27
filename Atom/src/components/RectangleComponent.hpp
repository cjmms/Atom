/*
* @file		RectangleComponent.hpp
* @author	Abhikalp Unakal
* @brief	RectangleComponent
* @date		2021-01-22
*/

#ifndef RECTANGLECOMPONENT_HPP
#define RECTANGLECOMPONENT_HPP
#include <Pch.hpp>
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class RectangleComponent {
public:
	glm::vec3 color;
	glm::vec2 scale;
	glm::vec2 position;
	bool wireframe;
};
// RENDERBOX COMPONENT SERDE
inline void to_json(ordered_json& j, const RectangleComponent& x) {
	to_json(j["color"], x.color);
	to_json(j["scale"], x.scale);
	to_json(j["position"], x.position);
	to_json(j["wireframe"], x.wireframe);
}

inline void from_json(const ordered_json& j, RectangleComponent& x) {
	from_json(j["color"], x.color);
	from_json(j["scale"], x.scale);
	from_json(j["position"], x.position);
	from_json(j["wireframe"], x.wireframe);
}

#endif // !RENDERCOMPONENT_HPP