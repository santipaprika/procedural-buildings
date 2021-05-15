#include "T.h"
#include <iostream>

T::T() 
{
    
}

T::T(glm::vec3 positionMax, glm::vec3 positionMin)
{
    this->positionMin = positionMin;
    this->positionMax = positionMax;
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
    
    float uniform = rand()/(float)RAND_MAX;
    glm::vec3 position = uniform * (positionMax - positionMin) + positionMin;
    
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

