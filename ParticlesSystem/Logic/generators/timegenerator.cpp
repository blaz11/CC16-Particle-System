#include "timegenerator.h"

TimeGenerator::TimeGenerator()
{

}

void TimeGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    for(size_t i=startId;i<endId;++i)
        p->m_time[i] = 5;
}
