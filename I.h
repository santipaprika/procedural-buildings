#pragma once

#include "Shape.h"

class I : public Shape
{
public:
    I(const std::string &objId_);
    ~I() override;
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType() override;
private:
    std::string objId;
};
