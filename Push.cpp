#include "Push.h"
#include <iostream>

Push::Push() 
{
    
}

Push::~Push()
{

}

bool Push::isTerminal()
{
    return true;
}

void Push::performAction(Context &context)
{
    context.pushScope(context.getTopScope());
    
    std::cout << "Pushing " << std::endl;
}

std::string Push::getShapeType()
{
    return "Push";
}

