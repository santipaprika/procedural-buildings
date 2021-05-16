#pragma once

#include "Context.h"
#include "Shape.h"


class R : public Shape
{
public:
    R(int axis_, float angleMin_, float angleMax_);
    ~R();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType() override;
private:
    int axis;
    float angleMin, angleMax;
};
