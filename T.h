#pragma once

#include "Context.h"
#include "Shape.h"


class T : public Shape
{
public:
    T();
    T(glm::vec3 positionMin, glm::vec3 positionMax);
    ~T();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
private:
    glm::vec3 positionMax;
    glm::vec3 positionMin;
};
