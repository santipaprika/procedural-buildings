#include "Grammar.h"
#include "Rule.h"
#include "Shape.h"

#include <iostream>
#include <list>

void generateGeometry(const std::list<Shape*> &shapes)
{
    Context context;
    for (Shape *shape : shapes) {
        shape->performAction(context);
    }

    for (Shape *shape : shapes) {
        if (shape) delete shape;
    }
}

// TODO:    Improve this algorithm by not traversing whole list every time
//          just detect shapes that are non-terminal when expanding and iterate over those in the next iteration
int main(){
    srand(time(NULL));

    Grammar grammar("../test.grammar");
    std::list<Shape*> shapes;
    shapes.push_back(grammar.initialShape());
    bool allTerminal = false;
    while (!allTerminal) {
        std::list<Shape*> nextShapes;
        allTerminal = true;
        while(!shapes.empty()) {
            Shape *shape = shapes.front();
            shapes.pop_front();
            if(!shape->isTerminal()) {
                Rule *rule = Grammar::findRule(shape);
                if (!rule) {
                    std::cerr << "E: No rule found for non-terminal shape, can't continue expanding." << std::endl;
                    std::exit(-1);
                }
                std::list<Shape*> expandedShapes = rule->expand(shape);
                nextShapes.splice(nextShapes.end(), expandedShapes);
                allTerminal = false;
            }
            else nextShapes.push_back(shape);
        }
        shapes = std::move(nextShapes);
    }
    generateGeometry(shapes);
}
