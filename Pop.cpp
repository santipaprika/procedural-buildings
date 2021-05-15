#include "Pop.h"
#include <iostream>

Pop::Pop() 
{
    
}

Pop::~Pop()
{

}

bool Pop::isTerminal()
{
    return true;
}

void Pop::performAction(Context &context)
{
    context.popScope();
    
    std::cout << "Popping " << std::endl;
}

std::string Pop::getShapeType()
{
    return "Pop";
}

