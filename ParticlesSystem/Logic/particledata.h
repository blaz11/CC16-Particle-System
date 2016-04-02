#ifndef PARTICLEDATA_H
#define PARTICLEDATA_H
#include <memory>
#include <glm/vec4.hpp>

class ParticleData
{
public:
    std::unique_ptr<glm::vec4[]> m_pos;
    std::unique_ptr<glm::vec4[]> m_vel;
    std::unique_ptr<glm::vec4[]> m_acc;
    std::unique_ptr<int[]> m_time;
    std::unique_ptr<bool[]>  m_alive;

    size_t m_count{ 0 };
    size_t m_countAlive{ 0 };
public:
    ParticleData(size_t maxCount);
    ~ParticleData() {}

    void generate(size_t maxSize);
    void kill(size_t id);
    void wake(size_t id);
    void swapData(size_t a, size_t b);
};

#endif // PARTICLEDATA_H
