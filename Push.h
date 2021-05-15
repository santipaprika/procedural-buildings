#pragma once

#include "Context.h"
#include "Shape.h"


class Push : public Shape
{
public:
    Push();
    ~Push();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
};
