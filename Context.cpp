#include "Context.h"

#include <iostream>

Context::Context()
{
    scopes.emplace(new Scope());
}

Context::~Context()
{

}

Scope* Context::getTopScope() const
{
    return scopes.top();
}

void Context::pushScope(Scope* scope) 
{
    scopes.push(scope);
}