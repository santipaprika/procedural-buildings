#include "R.h"

R::R(int axis_, float min_, float max_)
    : axis(axis_)
    , angleMin(min_)
    , angleMax(max_)
    {}

R::~R()
{

}

bool R::isTerminal()
{
    return true;
}

void R::performAction(Context &context)
{

    Scope &currentScope = context.getTopScope();
    float uniform = rand() / float(RAND_MAX);
    float angle = uniform * (angleMax - angleMin) + angleMin;

    switch(axis)
    {
        case 1:
            currentScope.Rx(angle);
        break;

        case 2:
            currentScope.Ry(angle);
        break;
        
        case 3:
            currentScope.Rz(angle);
        break;
    }
}

std::string R::getShapeType()
{
    return "R";
}