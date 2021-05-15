#pragma once

#include "Shape.h"

#include <string>

class NonTerminalShape : public Shape
{
public:
    NonTerminalShape(const std::string &type_);
    ~NonTerminalShape();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType() override;
private:
    std::string type;
};
