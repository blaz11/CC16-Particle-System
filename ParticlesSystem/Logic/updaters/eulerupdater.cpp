#include "eulerupdater.h"
#include <qdebug.h>
#include <glm/gtx/norm.hpp>
#include "glm/ext.hpp"

void EulerUpdater::update(double dt, ParticleData *p)
{
    const glm::vec4 globalA{ dt * m_globalAcceleration.x,
                             dt * m_globalAcceleration.y,
                             dt * m_globalAcceleration.z,
                             0.0 };
    const float localDT = (float)dt;

    const size_t endId = p->m_countAlive;

    PPCollisionDetector detector(localDT, p, R, touchTime);

    detector.updateAll();

    for (size_t i = 0; i < endId; ++i)
        p->m_vel[i] += localDT * p->m_acc[i];
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
            if(tmp < collTime && collTime >= 0)
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

    double a = length2(dv);
    double b = 2 * dot(dp, dv);
    double c = length2(dp);

    c -= 4*R*R;
    double delta = b*b - 4*a*c;
    if(delta < 0)
        return NO_COLLISION;

    double x1 = (-b-sqrt(delta))/(2*a);
    double x2 = (-b+sqrt(delta))/(2*a);

    //select lower non negative
    return glm::min(x1,x2);
}

glm::vec4 addVectors(glm::vec4 a, glm::vec4 b)
{
    return glm::vec4(a.x+b.x, a.y+b.y,a.z+b.z, a.w + b.w);
}

void PPCollisionDetector::handleCollision(double t, size_t i, size_t j)
{
    qDebug() << "Crash (" << i <<", " << j << ") @ "<<t;
    glm::vec3 pos1 = p->positionAtTime(i, t);
    glm::vec3 pos2 = p->positionAtTime(j, t);
    glm::vec3 dp = glm::vec3(pos1 - pos2);
    normalize(dp);
    glm::vec4 oldVel = p->m_vel[j];
    glm::vec3 dv = glm::vec3(p->m_vel[i].x - p->m_vel[j].x,
                   p->m_vel[i].y - p->m_vel[j].y,
                   p->m_vel[i].z - p->m_vel[j].z);
    glm::vec3 normalizedDv = dv;
    normalize(normalizedDv);

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
