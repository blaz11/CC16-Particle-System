#include "eulerupdater.h"

void EulerUpdater::update(double dt, ParticleData *p)
{
    const glm::vec4 globalA{ dt * m_globalAcceleration.x,
                             dt * m_globalAcceleration.y,
                             dt * m_globalAcceleration.z,
                             0.0 };
    const float localDT = (float)dt;

    const unsigned int endId = p->m_countAlive;
    for (size_t i = 0; i < endId; ++i)
        p->m_acc[i] += globalA;

    for (size_t i = 0; i < endId; ++i)
        p->m_vel[i] += localDT * p->m_acc[i];

    for (size_t i = 0; i < endId; ++i)
        p->m_pos[i] += localDT * p->m_vel[i];
}
