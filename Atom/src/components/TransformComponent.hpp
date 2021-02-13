#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
class TransformComponent {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 model;
};


// TRANSFORM COMPONENT SERDE
inline void to_json(ordered_json& j, const TransformComponent& x) {
    to_json(j["position"], x.position);
    to_json(j["rotation"], x.rotation);
    to_json(j["scale"], x.scale);
}

inline void from_json(const ordered_json& j, TransformComponent& x) {
    from_json(j["position"], x.position);
    from_json(j["rotation"], x.rotation);
    from_json(j["scale"], x.scale);
    x.model = glm::mat4(1.0);
}

#endif