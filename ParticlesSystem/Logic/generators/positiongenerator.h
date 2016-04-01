#ifndef POSITIONGENERATOR_H
#define POSITIONGENERATOR_H
#include "particlegenerator.h"

class PositionGenerator : public ParticleGenerator
{
public:
    PositionGenerator();
    virtual void generate(double dt, ParticleData *p, size_t startId, size_t endId);
};

#endif // POSITIONGENERATOR_H
