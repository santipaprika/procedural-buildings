#include "T.h"
#include <iostream>

T::T() 
{
    
}

T::T(glm::vec3 position)
{
    this->position = position;
}

T::~T()
{

}

bool T::isTerminal()
{
    return true;
}

void T::performAction(Context &context)
{
    Scope &newScope = context.getTopScope();
    newScope.T(position);

    std::cout << "T (" << position.x << ", " << position.y << ", " << position.z << ") ";
    glm::vec3 pos = context.getTopScope().getPosition();
    glm::vec3 size = context.getTopScope().getSize();
    std::cout << " -- Current scope -> POS: (" << pos.x << ", " << pos.y << ", " << pos.z << ") SIZE: (" << size.x << ", " << size.y << ", " << size.z << ") " << std::endl;
}

std::string T::getShapeType()
{
    return "T";
}

