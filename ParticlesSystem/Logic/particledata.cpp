#include "particledata.h"

ParticleData::ParticleData(size_t maxSize)
{
    generate(maxSize);
}

void ParticleData::generate(size_t maxSize)
{
    m_count = maxSize;
    m_countAlive = 0;

    m_pos.reset(new glm::vec4[maxSize]);
    m_vel.reset(new glm::vec4[maxSize]);
    m_acc.reset(new glm::vec4[maxSize]);
    m_time.reset(new int[maxSize]);
    m_alive.reset(new bool[maxSize]);
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
