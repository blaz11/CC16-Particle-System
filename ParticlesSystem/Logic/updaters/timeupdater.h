#ifndef TIMEUPDATER_H
#define TIMEUPDATER_H
#include "particleupdater.h"

class TimeUpdater : public ParticleUpdater
{
public:
    virtual void update(double dt, ParticleData *p) override;
};

#endif // TIMEUPDATER_H
