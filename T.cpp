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
        glm::vec4 positionHomogenous(position.x, position.y, position.z, 0.f);
        positionHomogenous = newScope.getTransform() * positionHomogenous;
        position = glm::vec3(positionHomogenous.x, positionHomogenous.y, positionHomogenous.z);
    }

    if (subdividing) {
        glm::vec4 positionHomogenous(abs(position.x), abs(position.y), abs(position.z), 0.f);
        positionHomogenous = newScope.getTransform() * positionHomogenous;
        // position = glm::vec3(positionHomogenous.x, positionHomogenous.y, positionHomogenous.z);
        if (position.x < 0) position.x = positionHomogenous.x;
        if (position.y < 0) position.y = positionHomogenous.y;
        if (position.z < 0) position.z = positionHomogenous.z;
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

