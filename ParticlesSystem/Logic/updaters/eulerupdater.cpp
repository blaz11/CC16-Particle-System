#include "eulerupdater.h"
#include <qdebug.h>
#include <glm/gtx/norm.hpp>
#include <qmath.h>
#include "glm/ext.hpp"

EulerUpdater::EulerUpdater()
{
    R = 1;
    touchTime = 0;
}

void EulerUpdater::update(double dt, ParticleData *p)
{
    const glm::vec4 globalA{ dt * p->globalAcceleration.x,
                             dt * p->globalAcceleration.y,
                             dt * p->globalAcceleration.z,
                             0.0 };
    const float localDT = (float)dt;

    const size_t endId = p->m_countAlive;

    p->nextFrame();

    PPCollisionDetector detector(localDT, p, R, touchTime);

    detector.updateAll();

    for (size_t i = 0; i < endId; ++i)
    {
        p->m_acc[i] = -6*M_PI*p->stickiness*R*p->m_vel[i];
        p->m_vel[i] += localDT * p->m_acc[i] + globalA;
        if(p->m_pos[i].y < -10)
            p->m_vel[i].y = -p->m_vel[i].y;
    }
}

PPCollisionDetector::PPCollisionDetector(double dt, ParticleData *p, double R, double touchTime)
{
    this->dt = dt;
    this->p = p;
    this->R = R;
    this->touchTime = touchTime;
}

void PPCollisionDetector::updateAll()
{
    for(size_t i = 0; i < p->m_countAlive; ++i)
    {
        double collTime = NO_COLLISION;
        size_t colliding = -1;
        for(size_t j = i+1; j < p->m_countAlive; ++j)
        {
            double tmp = collisionTime(i, j);
            if(tmp < collTime && tmp >= 0)
            {
                collTime = tmp;
                colliding = j;
            }
        }
        if(collTime < dt)
        {
            handleCollision(collTime, i, colliding);
            skipToEnd(dt-collTime-touchTime, i);
        }
        else
        {
            skipToEnd(dt, i);
        }
    }
}

//Solving equation at^2+bt+c = (2R)^2
double PPCollisionDetector::collisionTime(size_t i, size_t j)
{
    glm::vec3 dp = glm::vec3(p->m_pos[i] - p->m_pos[j]);
    glm::vec3 dv = glm::vec3(p->m_vel[i] - p->m_vel[j]);

    double a = dot(dv, dv);
    double b = 2 * dot(dp, dv);
    double c = dot(dp, dp);

    c -= 4*R*R;
    double delta = b*b - 4*a*c;
    if(delta < 0)
        return NO_COLLISION;

    double x1 = (-b-sqrt(delta))/(2*a);
    double x2 = (-b+sqrt(delta))/(2*a);

    return glm::min(x1,x2);
}

glm::vec4 addVectors(glm::vec4 a, glm::vec4 b)
{
    return glm::vec4(a.x+b.x, a.y+b.y,a.z+b.z, a.w + b.w);
}

void PPCollisionDetector::handleCollision(double t, size_t i, size_t j)
{
    glm::vec3 pos1 = p->positionAtTime(i, t);
    glm::vec3 pos2 = p->positionAtTime(j, t);

    p->m_pos[i] = glm::vec4(pos1, 0);
    p->m_pos[j] = glm::vec4(pos2, 0);
    glm::vec3 dp = glm::vec3(pos1 - pos2);
    dp = normalize(dp);
    glm::vec4 oldVel = p->m_vel[j];
    glm::vec3 dv = glm::vec3(p->m_vel[i].x - p->m_vel[j].x,
                   p->m_vel[i].y - p->m_vel[j].y,
                   p->m_vel[i].z - p->m_vel[j].z);
    glm::vec3 normalizedDv = dv;
    normalizedDv = normalize(normalizedDv);

    p->m_vel[i] = glm::vec4(dv,1);
    p->m_vel[i] *= dot(dp, normalizedDv);
    p->m_vel[j] = glm::vec4(dv,1);
    p->m_vel[j] *= length(cross(dp, normalizedDv));

    p->m_vel[i] = addVectors(p->m_vel[i], oldVel);
    p->m_vel[j] = addVectors(p->m_vel[j], oldVel);
}

void PPCollisionDetector::skipToEnd(double dt, size_t i)
{
    if(dt > 0)
    {
        glm::vec4 tmp = p->m_vel[i];
        tmp *= dt;
        p->m_pos[i] = addVectors(tmp, p->m_pos[i]);
    }
}
