#include "S.h"
#include <iostream>

S::S() 
{
    
}

S::S(glm::vec3 size)
{
    this->size = size;
}

S::~S()
{

}

bool S::isTerminal()
{
    return true;
}

void S::performAction(Context &context)
{
    Scope &newScope = context.getTopScope();
    std::cout << "S (" << size.x << ", " << size.y << ", " << size.z << ") ";
    if (size.x < 0) size.x = newScope.getSize().x;
    if (size.y < 0) size.y = newScope.getSize().y;
    if (size.z < 0) size.z = newScope.getSize().z;

    newScope.S(size);

    glm::vec3 pos = context.getTopScope().getPosition();
    glm::vec3 contextSize = context.getTopScope().getSize();
    std::cout << " -- Current scope -> POS: (" << pos.x << ", " << pos.y << ", " << pos.z << ") SIZE: (" << contextSize.x << ", " << contextSize.y << ", " << contextSize.z << ") " << std::endl;
}

std::string S::getShapeType()
{
    return "S";
}

