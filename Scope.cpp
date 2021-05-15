#include "Scope.h"

#include "glm/ext.hpp"

Scope::Scope()
    : position(0.0f)
    , size(1.0f)
    , x(1.0f, 0.0f, 0.0f)
    , y (0.0f, 1.0f, 0.0f)
    , z (0.0f, 0.0f, 1.0f)
    {}

Scope::Scope(const Scope &other)
    : position(other.position)
    , size(other.size)
    , x(other.x)
    , y(other.y)
    , z(other.z)
    {}

void Scope::T(const glm::vec3 &translation)
{
    position += translation;
}

void Scope::S(const glm::vec3 &size_)
{
    size = size_;
}

// TODO: Fix these rotations (make them local space not global)
void Scope::Rx(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, c, s), glm::vec3(0.0f, -s, c));
    y = rotation * y;
    z = rotation * z;

}

void Scope::Ry(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(c, 0.0f, -s), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(s, 0.0f, c));
    x = rotation * x;
    z = rotation * z;
}

void Scope::Rz(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(c, s, 0.0f), glm::vec3(-s, c, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    x = rotation * x;
    y = rotation * y;
}

glm::mat4 Scope::getTransform()
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, position);
    return transform;
}

glm::vec3 Scope::getPosition() const
{
    return position;
}

glm::vec3 Scope::getSize() const
{
    return size;
}
