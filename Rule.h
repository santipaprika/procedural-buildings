#pragma once

#include "Shape.h"

#include <list>
#include <string>
#include <vector>

class Rule
{
public:
    Rule(bool test);
    std::list<Shape*> expand(Shape *shape);

    // TODO: This could be a string?
    std::string left;
    std::vector<std::vector<Shape*>> right;
    std::vector<float> rightProbs;
};
