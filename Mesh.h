#pragma once

#include "glm/glm.hpp"

#include <string>
#include <vector>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void add(const Mesh &other);
    void apply(const glm::mat4 &transform);
    void addTriangle(int i0, int i1, int i2);
    void addQuad(int i0, int i1, int i2, int i3);
    static Mesh getInstance(const std::string &objId);
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> faces;
private:
    static Mesh getCube();
    static Mesh getSphere();
    static Mesh getCylinder();
};
