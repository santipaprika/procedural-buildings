#pragma once

#include "Context.h"
#include "Shape.h"

class S : public Shape
{
public:
    ~S();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
private:
    // TODO: Store information regarding its parameters
};
