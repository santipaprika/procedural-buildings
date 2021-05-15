#pragma once

#include "Scope.h"

#include <stack>

class Context
{
public:
    Context();
    ~Context();
    Scope &getTopScope();
    void pushScope(const Scope& scope);
    void popScope();
private:
    std::stack<Scope> scopes;
    // TODO: Store a triangle mesh where objects are instantiated
};