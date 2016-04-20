#include "positiongenerator.h"

PositionGenerator::PositionGenerator()
{
}

void PositionGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    glm::vec4 start = mainWin->sett->startPosition;
    for(size_t i=startId;i < endId;++i)
        p->m_pos[i] = glm::vec4(start.z + rand()%21-10, start.y+ rand()%21-10, -start.x + rand()%21-10, 0);
}
