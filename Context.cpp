#include "Context.h"

#include <iostream>

Context::Context()
{
    scopes.emplace();
}

Context::~Context()
{

}

void Context::S()
{
    std::cout << "S" << std::endl;
}