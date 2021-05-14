#include "Shape.h"


Shape::Shape() 
{
    label = FACADE;
    scope = nullptr;
}

Shape::Shape(Label label, Scope* scope) 
{
    this->label = label;
    this->scope = scope;
}

Shape::~Shape() 
{
    delete scope;
}
