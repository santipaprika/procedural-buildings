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
    static Mesh getInstance(const std::string &objId);

public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> faces;
private:
};
