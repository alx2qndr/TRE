#pragma once

#include <memory>

#include "Model.hpp"

namespace tre {

struct Transform2DComponent {
    glm::vec2 translation {};
    glm::vec2 scale { 1.0f, 1.0f };
    float rotation;

    glm::mat2 mat2() const
    {
        const float s = glm::sin(rotation);
        const float c = glm::cos(rotation);
        glm::mat2 rotMatrix { { c, s }, { -s, c } };

        glm::mat2 scaleMat { { scale.x, 0.0f }, { 0.0f, scale.y } };
        return rotMatrix * scaleMat;
    }
};

class Object {
public:
    using id_t = unsigned int;

    static Object create()
    {
        static id_t currentId = 0;
        return Object { currentId++ };
    }

    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(Object&&) = default;

    id_t getId() const { return id; }

    std::shared_ptr<Model> model {};
    glm::vec3 color {};
    Transform2DComponent transform2D {};

private:
    Object(id_t objId)
        : id { objId }
    {
    }

    id_t id;
};
} // namespace fre