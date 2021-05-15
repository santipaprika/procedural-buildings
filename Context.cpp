#include "Context.h"

#include <iostream>

Context::Context()
{
    scopes.emplace();
}

Context::~Context()
{

}

void Context::pushScope(const Scope &scope) 
{
    scopes.push(scope);
}

void Context::popScope() 
{
    scopes.pop();
}

Scope &Context::getTopScope()
{
    return scopes.top();
}

Mesh &Context::getScene()
{
    return scene;
}