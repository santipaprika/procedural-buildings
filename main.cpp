#include <iostream>
#include "glm/glm.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;
    glm::vec3 a(0.f);
    std::cout << glm::to_string(a) << std::endl;
    return 0;
}
