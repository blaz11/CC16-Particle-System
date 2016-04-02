#ifndef PARTICLEUPDATER_H
#define PARTICLEUPDATER_H
#include "../particledata.h"

class ParticleUpdater
{
public:
    ParticleUpdater();
    virtual ~ParticleUpdater() {}

    virtual void update(double dt, ParticleData *p) = 0;
};

#endif // PARTICLEUPDATER_H
