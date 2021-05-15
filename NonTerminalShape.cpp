#include "NonTerminalShape.h"

#include <iostream>

NonTerminalShape::NonTerminalShape(const std::string &type_)
    : type(type_)
    {}

NonTerminalShape::~NonTerminalShape()
{

}

bool NonTerminalShape::isTerminal()
{
    return false;
}

void NonTerminalShape::performAction(Context &context)
{
    std::cerr << "E: performAction(context) called on non-terminal shape" << std::endl;
}

std::string NonTerminalShape::getShapeType()
{
    return type;
}
