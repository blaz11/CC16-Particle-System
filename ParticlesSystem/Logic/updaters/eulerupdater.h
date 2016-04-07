#ifndef EULERUPDATER_H
#define EULERUPDATER_H
#include "particleupdater.h"

class PPCollisionDetector
{
public:
    const double NO_COLLISION = 1e55;
    PPCollisionDetector(double dt, ParticleData *p, double R, double touchTime);
    void updateAll();
private:
    double dt;
    ParticleData *p;
    double R;
    double touchTime;
    void updatePair(int i, int j);
    double collisionTime(size_t i, size_t j);
    void handleCollision(double t, size_t i, size_t j);
    void skipToEnd(double timeLeft, size_t i);
};


class EulerUpdater : public ParticleUpdater
{
public:
    glm::vec4 m_globalAcceleration{ 0.0f };
    double R;
    double touchTime;
public:
    virtual void update(double dt, ParticleData *p) override;
};

#endif // EULERUPDATER_H
