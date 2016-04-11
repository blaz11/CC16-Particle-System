#include "velocitygenerator.h"

VelocityGenerator::VelocityGenerator()
{

}

void VelocityGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    srand(time(NULL));
    for(size_t i=startId;i<endId;++i)
        p->m_vel[i] = glm::vec4((float)(rand()%11-5)/10,(float)(rand()%11-5)/10,(float)(rand()%11-5)/10,0);
}
