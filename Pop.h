#pragma once

#include "Context.h"
#include "Shape.h"


class Pop : public Shape
{
public:
    Pop();
    ~Pop();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
};
