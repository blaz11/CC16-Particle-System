#include "triangle.h"

Triangle::Triangle(float* v)
{
    for(int i=0;i<3;++i)
        this->v[i] = glm::vec3(v[3*i],v[3*i+1],v[3*i+2]);
}

