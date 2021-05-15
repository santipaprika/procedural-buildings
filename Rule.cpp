#include "Rule.h"

#include "S.h"
#include "NonTerminalShape.h"

Rule::Rule(bool test)
{
    // if (test) {
    //     ShapeInstanceInfo right_ = {"S"};
    //     left = {""};
    //     right = {{right_}};
    // }
}

std::list<Shape*> Rule::expand(Shape *shape)
{
    int alternatives = right.size();
    std::list<Shape*> result;
    std::vector<Shape*> expandedShapes = right[0]; // TODO: This should choose one of the alternatives randomly
    for (int i = 0; i < expandedShapes.size(); ++i) {
        result.push_back(expandedShapes[i]);
    }
    delete shape;
    return result;
}