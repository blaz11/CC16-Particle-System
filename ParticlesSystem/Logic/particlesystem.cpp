#include "particlesystem.h"
#include "generators/positiongenerator.h"
#include "generators/timegenerator.h"
#include "generators/velocitygenerator.h"
#include "updaters/timeupdater.h"
#include "updaters/eulerupdater.h"
#include "mainwindow.h"
using namespace std;

ParticleSystem::ParticleSystem(size_t maxParticles, MainWindow* mainWin)
    : particleData(maxParticles)
{
    this->maxParticles = maxParticles;
    initEmitter(mainWin);
}

void ParticleSystem::initEmitter(MainWindow* mainWin)
{
    auto emitter = make_shared<ParticleEmitter>(mainWin);
    std::shared_ptr<ParticleGenerator> pos = make_shared<PositionGenerator>();
    pos.get()->mainWin = mainWin;
    emitter->addGenerator(pos);
    std::shared_ptr<ParticleGenerator> vel = make_shared<VelocityGenerator>();
    vel.get()->mainWin = mainWin;
    emitter->addGenerator(vel);
    std::shared_ptr<ParticleGenerator> time = make_shared<TimeGenerator>();
    time.get()->mainWin = mainWin;
    emitter->addGenerator(time);
    emitters.push_back(emitter);
}

void ParticleSystem::initUpdaters()
{
    auto time = make_shared<TimeUpdater>();
    updaters.push_back(time);
    auto euler = make_shared<EulerUpdater>(triStart, triEnd);
    updaters.push_back(euler);
}

void ParticleSystem::initTriangles(float* triStart, float* triEnd)
{
    this->triStart = triStart;
    this->triEnd = triEnd;
    initUpdaters();
}

std::vector<glm::vec3> ParticleSystem::getParticlePositions()
{
    std::vector<glm::vec3> result;
    for(int i=0;i<particleData.m_countAlive;++i)
    {
        result.push_back(glm::vec3(particleData.m_pos[i]));
    }
    return result;
}

void ParticleSystem::update(double dt)
{
    for(auto updater = updaters.begin();updater != updaters.end();++updater)
        (*updater)->update(dt, &particleData);
    for(auto emitter = emitters.begin(); emitter != emitters.end();++emitter)
        (*emitter)->_emit(dt, &particleData);
}


