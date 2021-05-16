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

void Scope::Rx(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, c, s), glm::vec3(0.0f, -s, c));
    glm::mat3 basis(x, y, z);
    y = basis * rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    z = basis * rotation * glm::vec3(0.0f, 0.0f, 1.0f);

}

void Scope::Ry(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(c, 0.0f, -s), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(s, 0.0f, c));
    glm::mat3 basis(x, y, z);
    x = basis * rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    z = basis * rotation * glm::vec3(0.0f, 0.0f, 1.0f);
}

void Scope::Rz(float angle)
{
    float c = glm::cos(angle);
    float s = glm::sin(angle);
    glm::mat3 rotation(glm::vec3(c, s, 0.0f), glm::vec3(-s, c, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat3 basis(x, y, z);
    x = basis * rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    y = basis * rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Scope::getTransform()
{
    glm::mat4 rotation(glm::vec4(x, 0.0f), glm::vec4(y, 0.0f), glm::vec4(z, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::mat4 translation(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(position, 1.0f));
    glm::mat4 scale(glm::vec4(size.x, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, size.y, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, size.z, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    return glm::inverse(rotation) * translation * scale;
}

glm::vec3 Scope::getPosition() const
{
    return position;
}

glm::vec3 Scope::getSize() const
{
    return size;
}
