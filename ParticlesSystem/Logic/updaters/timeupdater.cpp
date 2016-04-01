#include "timeupdater.h"

void TimeUpdater::update(double dt, ParticleData *p)
{
    size_t endId = p->m_countAlive;
    const float localDT = (float)dt;
    for(size_t i=0;i<endId;++i)
    {
        p->m_time[i]-=localDT;
        if(p->m_time[i] < 0)
        {
            p->kill(i);
            --endId;
            --i;
        }
    }
}

