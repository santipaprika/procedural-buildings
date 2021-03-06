#pragma once

#include "Context.h"
#include "Shape.h"


class S : public Shape
{
public:
    S();
    S(glm::vec3 sizeMin, glm::vec3 sizeMax);
    ~S();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
private:
    glm::vec3 sizeMin;
    glm::vec3 sizeMax;
};
