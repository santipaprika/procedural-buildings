#pragma once

#include "Context.h"
#include "Shape.h"


class S : public Shape
{
public:
    S();
    S(glm::vec3 scale);
    ~S();
    bool isTerminal() override;
    void performAction(Context &context) override;
    std::string getShapeType();
private:
    glm::vec3 scale;
    // TODO: Store information regarding its parameters
};
