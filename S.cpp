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
    Scope* newScope = new Scope((*context.getTopScope()));
    newScope->S(scale);
    context.pushScope(newScope);

    // context.S();
    std::cout << "S (" << scale.x << ", " << scale.y << ", " << scale.z << ") ";
    glm::vec3 size = context.getTopScope()->getSize();
    std::cout << " -- Current scope -> POS: (" << size.x << ", " << size.y << ", " << size.z << ") SIZE: (" << size.x << ", " << size.y << ", " << size.z << ") " << std::endl;
}

std::string S::getShapeType()
{
    return "S";
}

