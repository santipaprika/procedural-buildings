#include "Rule.h"

#include "S.h"
#include "NonTerminalShape.h"

Rule::Rule(bool test)
{

}

std::list<Shape*> Rule::expand(Shape *shape)
{
    int alternatives = right.size();
    std::list<Shape*> result;

    int rightWinnerIdx = 0;
    float uniform = rand()/(float)RAND_MAX;
    float cumulativeProb = 0;
    for (int i=0; i<rightProbs.size(); i++) {
        cumulativeProb += rightProbs[i];
        if (cumulativeProb > uniform) {
            rightWinnerIdx = i;
            break;
        } 
    }

    std::vector<Shape*> expandedShapes = right[rightWinnerIdx];
    for (int i = 0; i < expandedShapes.size(); ++i) {
        result.push_back(expandedShapes[i]);
    }
    delete shape;
    return result;
}