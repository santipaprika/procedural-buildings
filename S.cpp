#include "S.h"

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
}

std::string S::getShapeType()
{
    return "S";
}