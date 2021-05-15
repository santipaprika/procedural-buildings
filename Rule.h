#pragma once

#include "Shape.h"

#include <list>
#include <string>
#include <vector>
// TODO: Move this to another place

struct ShapeInstanceInfo
{
    std::string type;
};

class Rule
{
public:
    Rule(bool test);
    std::list<Shape*> expand(Shape *shape);

    ShapeInstanceInfo left;
    std::vector<std::vector<ShapeInstanceInfo>> right;
private:
    Shape* instantiateShape(ShapeInstanceInfo shapeInstanceInfo);
};
