#include "velocitygenerator.h"

VelocityGenerator::VelocityGenerator()
{

}

void VelocityGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    for(size_t i=startId;i<endId;++i)
        p->m_vel[i] = glm::vec4(1,0,0,0);
}
