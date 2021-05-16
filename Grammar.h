#pragma once

#include "Rule.h"

#include <string>
#include <unordered_map>
#include <stack>

#define OUT


class Grammar
{
public:
    Grammar(const std::string &filePath);
    ~Grammar();
    static Rule* findRule(Shape *shape);
    Shape* initialShape() const;
    Shape* parseShapeParameters(std::string shapeType, std::istringstream& lin);
    void parseSubdivisionParameters(std::istringstream& lin, Rule* rule);

private:
    using ShapeInstanceType = std::string;
    static std::unordered_map<ShapeInstanceType, Rule*> substitutionRules;
    void parseRangeValue(std::istringstream &lin, float (&rangeValues)[2]);
    void parseRangeValues(std::istringstream& lin, float (&rangeValues)[6]);
};
