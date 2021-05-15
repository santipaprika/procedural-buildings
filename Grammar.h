#pragma once

#include "Rule.h"

#include <string>
#include <unordered_map>


class Grammar
{
public:
    Grammar(const std::string &filePath);
    ~Grammar();
    Rule* findRule(Shape *shape);
    Shape* initialShape() const;
    Shape* parseShapeParameters(std::string shapeType, std::istringstream& lin) const;
private:
    using ShapeInstanceType = std::string;
    std::unordered_map<ShapeInstanceType, Rule*> substitutionRules;
};
