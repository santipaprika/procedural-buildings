#include "S.h"
#include <iostream>

S::S() 
{
    
}

S::S(glm::vec3 scale)
{
    this->scale = scale;
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
    context.S();
    std::cout << "(" << scale.x << ", " << scale.y << ", " << scale.z << ") " << std::endl;
}

std::string S::getShapeType()
{
    return "S";
}

