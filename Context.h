#pragma once

#include "Scope.h"
#include "Mesh.h"

#include <stack>

class Context
{
public:
    Context();
    ~Context();
    void pushScope(const Scope& scope);
    void popScope();
    Scope &getTopScope();
    Mesh &getScene();
private:
    std::stack<Scope> scopes;
    Mesh scene;
};