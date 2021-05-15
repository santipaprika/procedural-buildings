#pragma once

#include "Rule.h"

#include <string>
#include <unordered_map>


class Grammar
{
public:
    Grammar(const std::string &filePath);
    ~Grammar();
    static Rule* findRule(Shape *shape);
    Shape* initialShape() const;
    Shape* parseShapeParameters(std::string shapeType, std::istringstream& lin) const;
    void parseSubdivisionParameters(std::istringstream& lin, Rule* rule);

private:
    using ShapeInstanceType = std::string;
    static std::unordered_map<ShapeInstanceType, Rule*> substitutionRules;
};
