#pragma once

#include "Context.h"

#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual bool isTerminal() = 0;
    virtual void performAction(Context &context) = 0;
    virtual std::string getShapeType() = 0;
};