#include "T.h"
#include <iostream>

T::T() 
{
    
}

T::T(glm::vec3 positionMax, glm::vec3 positionMin, bool relative, bool subdividing)
{
    this->positionMin = positionMin;
    this->positionMax = positionMax;

    this->relative = relative;
    this->subdividing = subdividing;
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
    
    glm::vec3 uniform(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
    glm::vec3 position = uniform * (positionMax - positionMin) + positionMin;
    
    if (relative) {
        position.x = position.x * newScope.getSize().x;
        position.y = position.y * newScope.getSize().y;
        position.z = position.z * newScope.getSize().z;
    }

    if (subdividing) {
        if (position.x < 0) position.x = abs(position.x) * newScope.getSize().x;
        if (position.y < 0) position.y = abs(position.y) * newScope.getSize().y;
        if (position.z < 0) position.z = abs(position.z) * newScope.getSize().z;
    }

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

