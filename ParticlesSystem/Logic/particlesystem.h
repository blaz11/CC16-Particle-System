#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "particledata.h"
#include "particleemitter.h"
#include "updaters/particleupdater.h"
#include <memory>
#include <glm/vec3.hpp>

class ParticleSystem
{
private:
    const double DEFAULT_EMIT_RATE = 0.4;
    size_t maxParticles;
    ParticleData particleData;
    std::vector<std::shared_ptr<ParticleEmitter>> emitters;
    std::vector<std::shared_ptr<ParticleUpdater>> updaters;
    float* triStart;
    float* triEnd;
public:
    ParticleSystem(size_t maxParticles, MainWindow* mainWin);
    void initTriangles(float* triStart, float* triEnd);
    void update(double dt);
    std::vector<glm::vec3> getParticlePositions();
private:
    void initEmitter(MainWindow* mainWin);
    void initUpdaters();
};

#endif // PARTICLESYSTEM_H
