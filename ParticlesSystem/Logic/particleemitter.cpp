#include "particleemitter.h"
#include <algorithm>

ParticleEmitter::ParticleEmitter(double m_emitRate)
{
    this->m_emitRate = m_emitRate;
}

void ParticleEmitter::_emit(double dt, ParticleData* p)
{
    const size_t maxNewParticles = static_cast<size_t>(dt*m_emitRate);
    const size_t startId = p->m_countAlive;
    const size_t endId = std::min(startId + maxNewParticles, p->m_count-1);

    for (auto &gen : m_generators)            // << gen loop
        gen->generate(dt, p, startId, endId);

    for (size_t i = startId; i < endId; ++i)  // << wake loop
        p->wake(i);
}

void ParticleEmitter::addGenerator(std::shared_ptr<ParticleGenerator> generator)
{
    m_generators.push_back(generator);
}
