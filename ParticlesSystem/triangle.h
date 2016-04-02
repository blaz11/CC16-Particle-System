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
    Cylinder()
    {
        double t1 = 1, step = M_PI/16;
        vector<glm::vec3> previousLine;
        for(double t2 = 0; t2 < 2*M_PI; t2 += step)
        {
            double x = 0.5*sin(t2);
            double y = 0.5*t1;
            double z = 0.5*cos(t2);
            glm::vec3 vec(x,y,z);
            previousLine.push_back(vec);
        }
        for(int i = 0 ; i < previousLine.size(); ++i)
        {
            Vertex v1(previousLine[i], glm::vec3(0, 1, 0));
            Vertex v2(previousLine[(i+1)%previousLine.size()], glm::vec3(0, 1, 0));
            Vertex v3(glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
            Triangle t(v1, v2, v3);
            triangles.push_back(t);
        }
        t1 = -1;
        vector<glm::vec3> nextLine;
        for(double t2 = 0; t2 < 2*M_PI; t2 += step)
        {
            double x = 0.5*sin(t2);
            double y = 0.5*t1;
            double z = 0.5*cos(t2);
            glm::vec3 vec(x,y,z);
            nextLine.push_back(vec);
        }
        for(int i = 0 ; i < nextLine.size(); ++i)
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
        for(int i = 0 ; i < nextLine.size(); ++i)
        {
            Vertex v1(nextLine[i], glm::vec3(0, -1, 0));
            Vertex v2(nextLine[(i+1)%nextLine.size()], glm::vec3(0, -1, 0));
            Vertex v3(glm::vec3(0, -0.5, 0), glm::vec3(0, -1, 0));
            Triangle t(v1, v2, v3);
            triangles.push_back(t);
        }
    }

    void generateDataForVBOs(vector<GLfloat>& poses, vector<GLfloat>& norms)
    {
        for(int i = 0 ; i < triangles.size(); ++i)
        {
            Triangle t = triangles[i];
            poses.push_back(t.vertex1.position.x);
            poses.push_back(t.vertex1.position.y);
            poses.push_back(t.vertex1.position.z);
            //qDebug() << t.vertex1.position.x << " " << t.vertex1.position.y << " " << t.vertex1.position.z << ";";
            norms.push_back(t.vertex1.normal.x);
            norms.push_back(t.vertex1.normal.y);
            norms.push_back(t.vertex1.normal.z);
        }
    }

private:
    vector<Triangle> triangles;

    glm::vec3 normalVector(glm::vec3 p)
    {
        glm::vec3 result(p.x, 0, p.z);
        return glm::normalize(result);
    }

};

#endif // TRIANGLE_H
