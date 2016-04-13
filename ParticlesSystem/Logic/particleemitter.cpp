#include "particleemitter.h"
#include <algorithm>

ParticleEmitter::ParticleEmitter(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void ParticleEmitter::_emit(double dt, ParticleData* p)
{
    int emitRate = mainWindow->sett->count;
    const size_t maxNewParticles = static_cast<size_t>(dt*emitRate);
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
