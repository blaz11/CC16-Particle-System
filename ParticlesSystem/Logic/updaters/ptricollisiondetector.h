#ifndef PTRICOLLISIONDETECTOR_H
#define PTRICOLLISIONDETECTOR_H
#include "../triangle.h"
#include "../particledata.h"
#include <vector>


class PTriCollisionDetector
{
private:
    ParticleData* p;
    float dt;
    float R;
    std::vector<Triangle> triangles;
public:
    const double NO_COLLISION = 1e55;
    PTriCollisionDetector(double dt, ParticleData *p, double R, std::vector<Triangle> triangles);
    void updateAll();
    double collisionTime(int id, Triangle& triangle);
    void handleCollision(float dt,int id, Triangle& triangle);
};

#endif // PTRICOLLISIONDETECTOR_H
