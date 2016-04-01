#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H
#include"../particledata.h"

class ParticleGenerator
{
public:
    ParticleGenerator();
    virtual void generate(double dt, ParticleData *p, size_t startId, size_t endId) = 0;
};

#endif // PARTICLEGENERATOR_H
