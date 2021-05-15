#include "S.h"
#include <iostream>

S::S() 
{
    
}

S::S(glm::vec3 sizeMin, glm::vec3 sizeMax)
{
    this->sizeMin = sizeMin;
    this->sizeMax = sizeMax;
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

    glm::vec3 uniform(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
    glm::vec3 size = uniform * (sizeMax - sizeMin) + sizeMin;

    std::cout << "S (" << size.x << ", " << size.y << ", " << size.z << ") ";

    size *= newScope.getSize();
    size = glm::vec3(abs(size.x), abs(size.y), abs(size.z));

    newScope.S(size);

    glm::vec3 pos = context.getTopScope().getPosition();
    glm::vec3 contextSize = context.getTopScope().getSize();
    std::cout << " -- Current scope -> POS: (" << pos.x << ", " << pos.y << ", " << pos.z << ") SIZE: (" << contextSize.x << ", " << contextSize.y << ", " << contextSize.z << ") " << std::endl;
}

std::string S::getShapeType()
{
    return "S";
}

