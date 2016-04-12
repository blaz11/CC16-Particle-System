#include "velocitygenerator.h"

VelocityGenerator::VelocityGenerator()
{

}

void VelocityGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    srand(time(NULL));
    for(size_t i=startId;i<endId;++i)
    {
        p->m_vel[i] = p->m_pos[i];
        p->m_vel[i] *= -0.05;
    }
}
