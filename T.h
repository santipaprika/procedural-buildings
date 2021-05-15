#pragma once

#include "Context.h"
#include "Shape.h"


class T : public Shape
{
public:
    T();
    T(glm::vec3 position);
    ~T();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
private:
    glm::vec3 position;
};
