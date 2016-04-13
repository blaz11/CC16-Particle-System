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
    double R;
    double touchTime;
public:
    EulerUpdater();
    virtual void update(double dt, ParticleData *p) override;
    glm::vec3 findCenter(ParticleData *p);
};

#endif // EULERUPDATER_H
