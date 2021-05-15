#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
    : vertices()
    , faces()
    {}

Mesh::~Mesh()
{

}

void Mesh::apply(const glm::mat4 &transform)
{
    for (auto &vertex : vertices)
        vertex = glm::vec3(transform * glm::vec4(vertex, 1.0));
}

void Mesh::add(const Mesh &other)
{
    int numVertices = vertices.size();
    vertices.insert(vertices.end(), other.vertices.begin(), other.vertices.end());

    for (const auto &face : other.faces)
        faces.emplace_back(face + glm::ivec3(numVertices));
}

Mesh Mesh::getInstance(const std::string &objId)
{
    if (objId != "Cube") {
        std::cerr << "W: Unknown primitive object type." << std::endl;
        std::cerr << "W: Defaulted to Cube." << std::endl;
    }

    Mesh instance;

    instance.vertices = {{1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {0, 1, 1},
                         {1, 0, 0}, {1, 1, 0}, {0, 0, 0}, {0, 1, 0}};

    instance.faces = {{0, 3, 2}, {0, 1, 3}, // TOP
                      {5, 4, 7}, {4, 6, 7}, // BOTTOM
                      {4, 0, 6}, {0, 2, 6}, // LEFT
                      {5, 3, 1}, {5, 7, 3}, // RIGHT
                      {4, 1, 0}, {5, 1, 4}, // FRONT
                      {2, 3, 6}, {6, 3, 7}  // BACK
    };

    return instance;
}