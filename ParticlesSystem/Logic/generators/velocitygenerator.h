#ifndef VELOCITYGENERATOR_H
#define VELOCITYGENERATOR_H
#include"particlegenerator.h"

class VelocityGenerator : public ParticleGenerator
{
public:
    VelocityGenerator();
    virtual void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};

#endif // VELOCITYGENERATOR_H
