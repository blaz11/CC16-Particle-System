#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glm/vec3.hpp>

struct Triangle
{
public:
    Triangle();
    Triangle(float* vertices);
    glm::vec3 v[3];
};

#endif // TRIANGLE_H
