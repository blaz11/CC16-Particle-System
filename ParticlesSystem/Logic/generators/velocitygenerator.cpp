#include "velocitygenerator.h"

VelocityGenerator::VelocityGenerator()
{

}

void VelocityGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    for(size_t i=startId;i<endId;++i)
    {
        float velocity = mainWin->sett->velocityValue;
        velocity /= 50;
        float variation = mainWin->sett->variation;
        variation /= 100;
        float x = mainWin->sett->valocityVector->x + variation * (rand()%41-20)/10;
        float y = mainWin->sett->valocityVector->y + variation * (rand()%41-20)/10;
        float z = mainWin->sett->valocityVector->z + variation * (rand()%41-20)/10;

        p->m_vel[i] = glm::vec4(z*velocity, y*velocity, -x*velocity, 0);
    }
}
