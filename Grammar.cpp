#include "Grammar.h"
#include "NonTerminalShape.h"
#include "S.h"
#include "T.h"
#include "Pop.h"
#include "Push.h"
#include "I.h"

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
        int rightIdx = 0;
        while (lin >> rightShapeType) {

            if (rightShapeType == ":") {
                float prob;
                std::string sep;
                lin >> prob >> sep;
                rule->rightProbs.push_back(prob); 
                rightIdx++;
                if (sep != "")
                    rule->right.push_back({});

                continue;
            }

            Shape* shape;
            if (rightShapeType == "S" || rightShapeType == "T" ||rightShapeType == "I") { // TO DO: If rightShapeType in *list of terminal shapes*
                shape = parseShapeParameters(rightShapeType, lin);
            } else if (rightShapeType == "[") {
                shape = new Push();
            } else if (rightShapeType == "]") {
                shape = new Pop();
            } else if (rightShapeType == "Subdiv") {
                parseSubdivisionParameters(lin, rule);
                continue;
            } else {
                shape = new NonTerminalShape(rightShapeType);
            }

            rule->right[rightIdx].push_back(shape);
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

Shape* Grammar::parseShapeParameters(std::string shapeType, std::istringstream& lin)
{
    // TO DO: Use switch instead of if?
    if (shapeType == "S") {
        float rangeValues[6];
        parseRangeValues(lin, OUT rangeValues);
        return new S(glm::vec3(rangeValues[0],rangeValues[1],rangeValues[2]), glm::vec3(rangeValues[3],rangeValues[4],rangeValues[5])); 
    }

    if (shapeType == "T") {
        float rangeValues[6];
        parseRangeValues(lin, OUT rangeValues);
        return new T(glm::vec3(rangeValues[0], rangeValues[1], rangeValues[2]),
                     glm::vec3(rangeValues[3], rangeValues[4], rangeValues[5]));
    }

    else if (shapeType == "I") {
        char parenthesis;
        std::string objId;
        lin >> parenthesis >> objId >> parenthesis;
        return new I(objId);
    }
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

    glm::vec3 dimVector(dim==1, dim==2, dim==3);
    std::vector<Shape*> shapes;
    lin >> parenthesis >> parenthesis;
    std::string shapeType;
    Shape* shape;
    for (int i=0; i<n; i++) {
        float size = cuts[i];
        glm::vec3 sizeVec((dim==1) ? size : -1, (dim==2) ? size : -1, (dim==3) ? size : -1);
        rule->right[0].push_back(new Push());
        rule->right[0].push_back(new T(dimVector * -cumulativeCuts[i],dimVector * -cumulativeCuts[i]));
        rule->right[0].push_back(new S(sizeVec,sizeVec));
        lin >> shapeType;
        if (shapeType == "S" || shapeType == "T") {
            shape = parseShapeParameters(shapeType, lin);
        } else {
            shape = new NonTerminalShape(shapeType);
        }
        
        rule->right[0].push_back(shape);
        rule->right[0].push_back(new Pop());

    }
    lin >> parenthesis;
}

void Grammar::parseRangeValues(std::istringstream& lin, float (&rangeValues)[6]) 
{
    char parenthesis;
    lin >> parenthesis; 
    std::string s;
    for (int i=0; i<3; i++) {
        lin >> s;
        if (s == "R") {
            lin >> s >> rangeValues[i] >> rangeValues[i+3] >> s; 
        } else {
            rangeValues[i] = atof(s.c_str());
            rangeValues[i+3] = rangeValues[i]; 
        }
    }

    lin >> parenthesis;
}
