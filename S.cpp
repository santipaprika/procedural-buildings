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
    Scope* newScope = new Scope((*context.getTopScope()));
    newScope->S(size);
    context.pushScope(newScope);

    std::cout << "S (" << size.x << ", " << size.y << ", " << size.z << ") ";
    glm::vec3 pos = context.getTopScope()->getPosition();
    // glm::vec3 size_ = context.getTopScope()->getSize();
    std::cout << " -- Current scope -> POS: (" << pos.x << ", " << pos.y << ", " << pos.z << ") SIZE: (" << size.x << ", " << size.y << ", " << size.z << ") " << std::endl;
}

std::string S::getShapeType()
{
    return "S";
}

