#pragma once
#include "Scope.h"

enum ShapeLabel {FACADE, WINDOW, FLOOR, ROOF, LEDGE};
using Label = int;

class Shape {
    private:
        Label label;
        Scope* scope;
    public:
        Shape();
        Shape(Label label, Scope* scope);

        ~Shape();
};

