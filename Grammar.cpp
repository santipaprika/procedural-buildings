#include "Grammar.h"
#include "NonTerminalShape.h"
#include "S.h"

#include <fstream>
#include <iostream>
#include <sstream>

Grammar::Grammar(const std::string &filePath)
{
    // TODO: Implement
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        std::cerr << "E: Could not open file " << filePath << std::endl;
        return;
    }

    std::string line;
    while(std::getline(fin, line)) {
        std::istringstream lin(line);

        char arrow;
        std::string leftShapeType, rightShapeType;
        lin >> leftShapeType >> arrow >> arrow;
        Rule *rule = new Rule(false);
        rule->left = {leftShapeType};
        rule->right = {{}};
        while (lin >> rightShapeType) {
            Shape* shape;
            if (rightShapeType == "S" || rightShapeType == "Subdiv") { // TO DO: If rightShapeType in *list of parametric shapes*
                shape = parseShapeParameters(rightShapeType, lin);
            } else {
                shape = new NonTerminalShape(rightShapeType);
            }
            rule->right[0].push_back(shape);
        }
        substitutionRules[leftShapeType] = rule;
    }
}

Grammar::~Grammar()
{

}

Rule* Grammar::findRule(Shape *shape)
{
    return substitutionRules[shape->getShapeType()];
}

// TODO: Implement non terminal shape S
Shape* Grammar::initialShape() const
{
    return new NonTerminalShape("X");
}

Shape* Grammar::parseShapeParameters(std::string shapeType, std::istringstream& lin) const
{
    // TO DO: Use switch instead of if?
    if (shapeType == "S") {
        char parenthesis;
        int s1, s2, s3;
        lin >> parenthesis >> s1 >> s2 >> s3 >> parenthesis;
        return new S(glm::vec3(s1,s2,s3)); 
    }

    // ...
}
