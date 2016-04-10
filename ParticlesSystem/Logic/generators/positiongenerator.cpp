#include "positiongenerator.h"

PositionGenerator::PositionGenerator()
{
}

void PositionGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    srand(time(NULL));
    for(size_t i=startId;i < endId;++i)
        p->m_pos[i] = glm::vec4(rand()%21-10,rand()%21-10,rand()%21-10,0);
}
