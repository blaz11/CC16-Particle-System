#include "particledata.h"
#include <glm/vec3.hpp>

ParticleData::ParticleData(size_t maxSize)
{
    generate(maxSize);
    globalAcceleration = glm::vec3(0,-0.1,0);
    stickiness = 0.0089;
}

void ParticleData::generate(size_t maxSize)
{
    m_count = maxSize;
    m_countAlive = 0;

    m_pos.reset(new glm::vec3[maxSize]);
    m_vel.reset(new glm::vec3[maxSize]);
    m_acc.reset(new glm::vec3[maxSize]);
    m_time.reset(new float[maxSize]);
    m_alive.reset(new bool[maxSize]);
    hasMoved.reset(new bool[maxSize]);
}

void ParticleData::kill(size_t id)
{
    if (m_countAlive > 0)
    {
        m_alive[id] = false;
        swapData(id, m_countAlive - 1);
        m_countAlive--;
    }
}

void ParticleData::wake(size_t id)
{
    if (m_countAlive < m_count)
    {
        m_alive[id] = true;
        swapData(id, m_countAlive);
        m_countAlive++;
    }
}

void ParticleData::swapData(size_t a, size_t b)
{
    std::swap(m_pos[a], m_pos[b]);
    std::swap(m_vel[a], m_vel[b]);
    std::swap(m_acc[a], m_acc[b]);
    std::swap(m_time[a], m_time[b]);
    std::swap(m_alive[a], m_alive[b]);
}


glm::vec3 ParticleData::positionAtTime(size_t i, double t)
{
    glm::vec3 tmp = glm::vec3(m_vel[i]);
    tmp *= t;
    tmp += glm::vec3(m_pos[i]);
    return tmp;
}

void ParticleData::nextFrame()
{
    for(int i=0;i < m_countAlive; ++i)
        hasMoved[i] = false;
}

void ParticleData::skipToEnd(size_t id, float dt)
{
    hasMoved[id] = true;
    if(dt > 0)
    {
        glm::vec3 tmp = m_vel[id]*dt;
        m_pos[id] = tmp + m_pos[id];
    }
}
