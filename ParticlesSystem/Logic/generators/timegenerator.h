#ifndef TIMEGENERATOR_H
#define TIMEGENERATOR_H
#include "particlegenerator.h"

class TimeGenerator : public ParticleGenerator
{
public:
    TimeGenerator();
    virtual void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};

#endif // TIMEGENERATOR_H
