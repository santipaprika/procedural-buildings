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
        rule->left = leftShapeType;
        rule->right = {{}};
        while (lin >> rightShapeType) {
            Shape* shape;
            if (rightShapeType == "S") { // TO DO: If rightShapeType in *list of terminal shapes*
                shape = parseShapeParameters(rightShapeType, lin);
            } else if (rightShapeType == "Subdiv") {
                parseSubdivisionParameters(lin, rule);
                continue;
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

std::unordered_map<std::string, Rule*> Grammar::substitutionRules;

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
        float s1, s2, s3;
        lin >> parenthesis >> s1 >> s2 >> s3 >> parenthesis;
        return new S(glm::vec3(s1,s2,s3)); 
    }

    // ...
}

void Grammar::parseSubdivisionParameters(std::istringstream& lin, Rule* rule) 
{
    char parenthesis;
    int dim;
    float n;
    lin >> parenthesis >> dim >> n;

    std::vector<float> cuts;
    float cut;
    // store cuts and cumulativeCuts
    std::vector<float> cumulativeCuts;
    for (int i=0; i<n; i++) {
        lin >> cut;
        cuts.push_back(cut);
        cumulativeCuts.push_back((i>0) ? cumulativeCuts.back() + cuts[i-1] : 0); 
    }

    std::vector<Shape*> shapes;
    lin >> parenthesis >> parenthesis;
    std::string shapeType;
    Shape* shape;
    for (int i=0; i<n; i++) {
        float scaleValue = cuts[i]; // TODO: Last element cas
        glm::vec3 scale((dim==1) ? scaleValue : 1, (dim==2) ? scaleValue : 1, (dim==3) ? scaleValue : 1);
        rule->right[0].push_back(new S(scale));
        // rule->right[0].push_back(new T(dimVector * cumulativeCuts[i]));
        lin >> shapeType;
        if (shapeType == "S") { // TO DO: If rightShapeType in *list of terminal shapes*
            shape = parseShapeParameters(shapeType, lin);
        } else {
            shape = new NonTerminalShape(shapeType);
        }
        
        rule->right[0].push_back(shape);
    }
    lin >> parenthesis;
}
