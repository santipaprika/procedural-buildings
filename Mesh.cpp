#include "Mesh.h"

#include "glm/ext.hpp"

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

void Mesh::addTriangle(int i0, int i1, int i2)
{
    faces.emplace_back(i0, i1, i2);
}

void Mesh::addQuad(int i0, int i1, int i2, int i3)
{
    addTriangle(i0, i1, i2);
    addTriangle(i0, i2, i3);
}

Mesh Mesh::getInstance(const std::string &objId)
{
    if (objId == "Cylinder") {
        return getCylinder();
    }

    if (objId == "Sphere") {
        return getSphere();
    }

    else if (objId != "Cube") {
        std::cerr << "W: Unknown primitive object type." << std::endl;
        std::cerr << "W: Defaulted to Cube." << std::endl;
    }

    return getCube();
}

Mesh Mesh::getCube()
{
    Mesh cube;

    cube.vertices = {{0.5, 0, 0.5}, {0.5, 1, 0.5}, {-0.5, 0, 0.5}, {-0.5, 1, 0.5},
                    {0.5, 0, -0.5}, {0.5, 1, -0.5}, {-0.5, 0, -0.5}, {-0.5, 1, -0.5}};

    cube.faces =    {{0, 3, 2}, {0, 1, 3}, // TOP
                    {5, 4, 7}, {4, 6, 7}, // BOTTOM
                    {4, 0, 6}, {0, 2, 6}, // LEFT
                    {5, 3, 1}, {5, 7, 3}, // RIGHT
                    {4, 1, 0}, {5, 1, 4}, // FRONT
                    {2, 3, 6}, {6, 3, 7}  // BACK
    };

    return cube;
}

Mesh Mesh::getCylinder()
{
    const int n = 40;
    float R = 0.5f;
    float pi = glm::pi<float>();
    glm::vec3 translation(0.5f, 0.0f, 0.5f); // Translation that has to be added to make the origin be at the bottom left corner
    Mesh cylinder;

    // Bottom vertices
    cylinder.vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f) + translation);
    for (int i = 1; i < n; ++i) {
        float t = float(i)/float(n);
        glm::vec3 baseVertex = glm::vec3(R*glm::cos(2*pi*t), 0.0f, R*glm::sin(2*pi*t)) + translation;
        cylinder.vertices.push_back(baseVertex);
        cylinder.faces.push_back(glm::ivec3(i + 1, 0, i));
    }
    cylinder.vertices.push_back(glm::vec3(R, 0.0f, 0.0f) + translation);
    cylinder.faces.push_back(glm::ivec3(1, 0, n));

    int topOffset = n + 1;

    // Top Vertices
    cylinder.vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0f) + translation);
    for (int i = 1; i < n; ++i) {
        float t = float(i)/float(n);
        glm::vec3 topVertex = glm::vec3(R*glm::cos(2*pi*t), 1.0f, R*glm::sin(2*pi*t)) + translation;
        cylinder.vertices.push_back(topVertex);
        cylinder.faces.push_back(glm::ivec3(i + topOffset, topOffset, i + 1 + topOffset));
        cylinder.faces.push_back(glm::ivec3(i + 1 + topOffset, i, i + topOffset));
        cylinder.faces.push_back(glm::ivec3(i, i + 1 + topOffset, i + 1));
    }
    cylinder.vertices.push_back(glm::vec3(R, 1.0f, 0.0f) + translation);
    cylinder.faces.push_back(glm::ivec3(n + topOffset, topOffset, 1 + topOffset));
    cylinder.faces.push_back(glm::ivec3(1 + topOffset, n, n + topOffset));
    cylinder.faces.push_back(glm::ivec3(n, 1 + topOffset, 1));

    return cylinder;
}


Mesh Mesh::getSphere()
{
    const int n_phi = 20; // Goes from 0 to pi
    const int n_theta = 40; // Goes from 0 to 2*pi
    const float R = 0.5f;
    const float pi = glm::pi<float>();
    Mesh sphere;

    // Add north pole
    glm::vec3 northPole = glm::vec3(0.0f, R, 0.0f);
    sphere.vertices.push_back(northPole);

    // Add layer connected to north pole
    float t_phi = float(1)/float(n_phi);
    float c_phi = glm::cos(pi * t_phi);
    float s_phi = glm::sin(pi * t_phi);

    for (int i = 1; i < n_theta; ++i) {
        float t_theta = float(i)/float(n_theta);
        float c_theta = glm::cos(2*pi * t_theta);
        float s_theta = glm::sin(2*pi * t_theta);

        glm::vec3 vertex = R * glm::vec3(s_phi * c_theta, c_phi, s_phi * s_theta);
        sphere.vertices.push_back(vertex);
        sphere.addTriangle(i+1, i, 0);
    }
    sphere.vertices.push_back(R * glm::vec3(s_phi, c_phi, 0.0f));
    sphere.addTriangle(1, n_theta, 0);

    int offset = n_theta;

    // Add middle layers
    for (int j = 2; j < n_phi; ++j) {
        t_phi = float(j)/float(n_phi);
        c_phi = glm::cos(pi * t_phi);
        s_phi = glm::sin(pi * t_phi);
        for (int i = 1; i < n_theta; ++i) {
            float t_theta = float(i)/float(n_theta);
            float c_theta = glm::cos(2*pi * t_theta);
            float s_theta = glm::sin(2*pi * t_theta);

            glm::vec3 vertex = R * glm::vec3(s_phi * c_theta, c_phi, s_phi * s_theta);
            sphere.vertices.push_back(vertex);
            sphere.addQuad(i+1 + offset, i + offset, i + offset - n_theta, i+1 + offset - n_theta);
        }
        sphere.vertices.push_back(R * glm::vec3(s_phi, c_phi, 0.0f));
        sphere.addQuad(1 + offset, n_theta + offset, offset, 1 + offset - n_theta);
        offset += n_theta;
    }

    // Add layer connected to south pole
    for (int i = 1; i < n_theta; ++i) {
        float t_theta = float(i)/float(n_theta);
        float c_theta = glm::cos(2*pi * t_theta);
        float s_theta = glm::sin(2*pi * t_theta);
        glm::vec3 vertex = R * glm::vec3(s_phi * c_theta, c_phi, s_phi * s_theta);
        sphere.vertices.push_back(vertex);
        sphere.addTriangle(i+1 + offset, n_theta + 1 + offset, i + offset);
    }
    sphere.vertices.push_back(R * glm::vec3(s_phi, c_phi, 0.0f));
    sphere.addTriangle(1 + offset, n_theta + 1 + offset, n_theta + offset);

    // Add north pole
    glm::vec3 southPole = glm::vec3(0.0f, -R, 0.0f);
    sphere.vertices.push_back(southPole);
    
    return sphere;
}
