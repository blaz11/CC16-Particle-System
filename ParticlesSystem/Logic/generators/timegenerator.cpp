#include "timegenerator.h"

TimeGenerator::TimeGenerator()
{

}

void TimeGenerator::generate(double dt, ParticleData *p, size_t startId, size_t endId)
{
    int time = mainWin->sett->liveTime;
    for(size_t i=startId;i<endId;++i)
        p->m_time[i] = time;
}
