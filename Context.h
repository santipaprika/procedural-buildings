#pragma once

#include "Scope.h"

#include <stack>

class Context
{
public:
    Context();
    ~Context();
    void S();
private:
    std::stack<Scope> scopes;
    // TODO: Store a triangle mesh where objects are instantiated
};