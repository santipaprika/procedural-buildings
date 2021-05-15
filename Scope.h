#pragma once
#include "glm/glm.hpp"

class Scope
{
public:
    Scope();
    Scope(const Scope &other);
    void T(const glm::vec3 &translation);
    void S(const glm::vec3 &size);
    void Rx(float angle);
    void Ry(float angle);
    void Rz(float angle);
    // TODO: glm::mat4 getTransform();

    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;

private:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 x, y, z;
};
