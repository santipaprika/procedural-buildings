#pragma once

#include "Mesh.h"

#include <fstream>
#include <string>

class PLYWriter
{
public:
    static bool writeMesh(const std::string &filename, const Mesh &mesh);

private:
    static void writeHeader(std::ofstream &fout, const Mesh &mesh);
    static void writeVertices(std::ofstream &fout, const Mesh &mesh);
    static void writeFaces(std::ofstream &fout, const Mesh &mesh);
};