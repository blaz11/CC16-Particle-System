#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H
#include"generators/particlegenerator.h"
#include"particledata.h"
#include <vector>

class ParticleEmitter
{
private:
    double m_emitRate;
    std::vector<std::shared_ptr<ParticleGenerator>> m_generators;
    MainWindow* mainWindow;
public:
    ParticleEmitter(MainWindow* mainWindow);
    void _emit(double dt, ParticleData *p);
    void addGenerator(std::shared_ptr<ParticleGenerator> generator);
};

#endif // PARTICLEEMITTER_H
