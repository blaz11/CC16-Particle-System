#ifndef EULERUPDATER_H
#define EULERUPDATER_H
#include "particleupdater.h"

class EulerUpdater : public ParticleUpdater
{
public:
    glm::vec4 m_globalAcceleration{ 0.0f };
public:
    virtual void update(double dt, ParticleData *p) override;
};

#endif // EULERUPDATER_H
