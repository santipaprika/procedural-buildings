#include "Context.h"

#include <iostream>

Context::Context()
{
    scopes.emplace();
}

Context::~Context()
{

}

Scope &Context::getTopScope()
{
    return scopes.top();
}

void Context::pushScope(const Scope &scope) 
{
    scopes.push(scope);
}

void Context::popScope() 
{
    scopes.pop();
}