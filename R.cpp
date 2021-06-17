#include "R.h"
#define DEG2RAD 0.017453292

R::R(int axis_, float min_, float max_)
    : axis(axis_)
    , angleMin(DEG2RAD * min_)
    , angleMax(DEG2RAD * max_)
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