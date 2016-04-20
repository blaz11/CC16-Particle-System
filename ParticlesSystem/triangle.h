#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "glm/common.hpp"
#include <qmath.h>
#include <Libraries/glm/gtc/matrix_transform.hpp>
#include <Libraries/glm/gtc/type_ptr.hpp>
#include <Libraries/glm/vec3.hpp>
#include <Libraries/glm/glm.hpp>
#include <QOpenGLFunctions>
#include <vector>
#include <QDebug>

using namespace std;

class Vertex
{
public:
    Vertex(glm::vec3 pos, glm::vec3 norm)
    {
        position = pos;
        normal = norm;
    }
    glm::vec3 position, normal;

};

class Triangle
{
public:
    Triangle(Vertex v1, Vertex v2, Vertex v3) : vertex1(v1), vertex2(v2), vertex3(v3)
    {
    }

    Vertex vertex1, vertex2, vertex3;

    static vector<Triangle> FromQuadrilateral(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4,
                                              glm::vec3 n1, glm::vec3 n2, glm::vec3 n3, glm::vec3 n4)
    {
        vector<Triangle> res;
        Vertex v11(p1, n1);
        Vertex v12(p2, n2);
        Vertex v13(p3, n3);
        Triangle t1(v11, v12, v13);
        Vertex v21(p1, p1);
        Vertex v22(p3, n3);
        Vertex v23(p4, n4);
        Triangle t2(v21, v22, v23);
        res.push_back(t1);
        res.push_back(t2);
      //  foreach (Triangle t in res)
      //      foreach (Vertex v in t.Vertices)
      //          v.Normal.Normalize();
        return res;
    }

};

class Cylinder
{
public:
    Cylinder(double angle, double size, glm::vec3 translation)
    {
        this->angle = angle;
        this->translation = translation;
        this->size = size;

        double t1 = 1, step = M_PI/16;
        vector<glm::vec3> previousLine;
        for(double t2 = 2*M_PI; t2 > 0; t2 -= step)
        {
            double x = 0.5*sin(t2)*t1;
            double y = 0.5*t1;
            double z = 0.5*cos(t2)*t1;
            previousLine.push_back(calculateVec(x, y, z));
        }
        t1 = -1;
        vector<glm::vec3> nextLine;
        for(double t2 = 3*M_PI; t2 > M_PI; t2 -= step)
        {
            double x = 0.5*sin(t2)*t1;
            double y = 0.5*t1;
            double z = 0.5*cos(t2)*t1;
            nextLine.push_back(calculateVec(x, y, z));
        }
        for(uint  i = 0 ; i < nextLine.size(); ++i)
        {
            vector<Triangle> ts = Triangle::FromQuadrilateral(
                    nextLine[i % nextLine.size()],
                    nextLine[(i + 1) % nextLine.size()],
                    previousLine[(i + 1) % previousLine.size()],
                    previousLine[i % previousLine.size()],
                    normalVector(nextLine[i % nextLine.size()]),
                    normalVector(nextLine[(i + 1) % nextLine.size()]),
                    normalVector(nextLine[i % previousLine.size()]),
                    normalVector(nextLine[(i + 1) % previousLine.size()]));
            triangles.push_back(ts[0]);
            triangles.push_back(ts[1]);
        }
    }

    void generateDataForVBOs(vector<GLfloat>& poses, vector<GLfloat>& norms)
    {
        for(uint  i = 0 ; i < triangles.size(); ++i)
        {
            Triangle t = triangles[i];
            poses.push_back(t.vertex1.position.x);
            poses.push_back(t.vertex1.position.y);
            poses.push_back(t.vertex1.position.z);
            norms.push_back(t.vertex1.normal.x);
            norms.push_back(t.vertex1.normal.y);
            norms.push_back(t.vertex1.normal.z);

            poses.push_back(t.vertex2.position.x);
            poses.push_back(t.vertex2.position.y);
            poses.push_back(t.vertex2.position.z);
            norms.push_back(t.vertex2.normal.x);
            norms.push_back(t.vertex2.normal.y);
            norms.push_back(t.vertex2.normal.z);

            poses.push_back(t.vertex3.position.x);
            poses.push_back(t.vertex3.position.y);
            poses.push_back(t.vertex3.position.z);
            norms.push_back(t.vertex3.normal.x);
            norms.push_back(t.vertex3.normal.y);
            norms.push_back(t.vertex3.normal.z);
        }
    }

private:
    vector<Triangle> triangles;
    double angle;
    double size;
    glm::vec3 translation;

    glm::vec3 normalVector(glm::vec3 p)
    {
        glm::vec3 result(p.x, 0, p.z);
        return glm::normalize(result);
    }

    glm::vec3 rotate(glm::vec3 vec, double angle)
    {
        double y = vec.y * cos(angle) - vec.z * sin(angle);
        double z = vec.y * sin(angle) + vec.z * cos(angle);
        glm::vec3 newVec(vec.x, y, z);
        return newVec;
    }

    glm::vec3 calculateVec(double x, double y, double z)
    {
        glm::vec3 vec(x,y,z);
        glm::vec3 final = rotate(vec, angle);
        final.x *= size;
        final.y *= size;
        final.z *= size;
        final.x += translation.x;
        final.y += translation.y;
        final.z += translation.z;
        return final;
    }

};

#endif // TRIANGLE_H
