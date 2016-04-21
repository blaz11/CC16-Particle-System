#include "ptricollisiondetector.h"
#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include <qdebug.h>
#include "glm/ext.hpp"

PTriCollisionDetector::PTriCollisionDetector(double dt, ParticleData *p, double R, std::vector<Triangle> triangles)
{
    this->dt = dt;
    this->p = p;
    this->R = R;
    this->triangles = triangles;
}

void PTriCollisionDetector::updateAll()
{
    for(int i=0;i<p->m_countAlive;++i)
    {
        double t = NO_COLLISION;
        int triangleId = -1;
        for(int j=0;j < triangles.size();++j)
        {
            double t1 = collisionTime(i, triangles[j]);
            if(t1 < t)
            {
                t = t1;
                triangleId = j;
            }
        }
        if(t > dt)
            continue;
        handleCollision(dt, i, triangles[triangleId]);
        p->skipToEnd(i, dt);
    }
}

//http://geomalgorithms.com/a06-_intersect-2.html
double PTriCollisionDetector::collisionTime(int id, Triangle& triangle)
{
    glm::vec3 I;
    glm::vec3 u = triangle.v[1] - triangle.v[0];
    glm::vec3 v = triangle.v[2] - triangle.v[0];
    glm::vec3 n = glm::cross(u,v);
    glm::vec3 dir = p->m_vel[id];
    glm::vec3 w0 = p->m_pos[id] - triangle.v[0];
    float a = -glm::dot(n,w0);
    float b = glm::dot(n, dir);
    if(fabs(b) < 1e-5) {
        if(a == 0) //in the same plane - let them collide
            return 0;
        else
            return NO_COLLISION; //ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    float r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return NO_COLLISION;        // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    I = p->m_pos[id] + r * dir;            // intersect point of ray and plane

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = glm::dot(u,u);
    uv = glm::dot(u,v);
    vv = glm::dot(v,v);
    glm::vec3 w = I - triangle.v[0];
    wu = glm::dot(w,u);
    wv = glm::dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
        return NO_COLLISION;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return NO_COLLISION;

    return length(I-p->m_pos[id])/length(p->m_vel[id]); // I is in T
}


void PTriCollisionDetector::handleCollision(float dt,int id, Triangle& triangle)
{
    p->m_pos[id]+=p->m_vel[id]*dt;
    glm::vec3 toParticle = -p->m_vel[id];
    glm::vec3 n = glm::cross(triangle.v[1]-triangle.v[0], triangle.v[2]-triangle.v[0]);
    glm::vec3 newV = 2*glm::dot(toParticle, n)*n - toParticle;
    p->m_vel[id] = newV;
}
