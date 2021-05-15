#include "I.h"
#include "Mesh.h"

#include <iostream>

I::I(const std::string &objId_)
    : objId(objId_)
    {}

I::~I()
{

}

bool I::isTerminal()
{
    return true;
}

void I::performAction(Context &context)
{
    glm::mat4 transform = context.getTopScope().getTransform();
    Mesh instance = Mesh::getInstance(objId);
    instance.apply(transform);
    context.getScene().add(instance);
    std::cout << "Instantiating a " << objId << std::endl;
}

std::string I::getShapeType()
{
    return "I";
}