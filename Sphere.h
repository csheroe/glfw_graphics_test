#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include "glm/glm.hpp"					// NOTE: Need to compile, hence the quotes
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cstring>
#include <sstream>
#include "HitRecord.h"

using namespace std;

class Sphere
{
  private:
    glm::vec3 position=glm::vec3(0,0,0);
    double radius = 1;
    int mat_Index = -1; //material index
  public:
    Sphere()
    {
    };
    Sphere(glm::vec3 center, double radius)
    {
      position=center;
      this -> radius=radius;
    };
    glm::vec3 getCenter()
    {
      return position;
    };
    void setMaterialIndex(int mat_Index)
    {
      this ->mat_Index=mat_Index;
    };
    int getMaterialIndex()
    {
      return mat_Index;
    };
    double getRadius()
    {
      return radius;
    };
    void read(string data) //expects a string formatted like (s x y z radius)
    //where s x y z and radius are all floating point numbers
    {
      stringstream ss(data);
      char dummy[80];
      ss >> dummy;
      ss >> position.x >> position.y >> position.z >> radius;
    };
    string toString() //returns a string formatted like (s x y z radius)
    {
      string output= "s ";
      output += to_string(position.x)+" ";
      output += to_string(position.y)+" ";
      output += to_string(position.z)+" ";
      output += to_string(radius);
      return output;
    };
    bool getIntersection(glm::vec3 rayStart, glm::vec3 rayDir, HitRecord &record)
    {
    glm::vec3 E = rayStart;
    glm::vec3 D = rayDir;
    glm::vec3 C = position;
    double r = radius;
    glm::vec3 EmC = E-C;
    double Ddot = glm::dot(D,D);
    double DdEmC;
    DdEmC = (glm::dot(D,EmC));
    double a = DdEmC*DdEmC;
    double b;
    b = (Ddot)*(glm::dot(EmC,EmC)-r*r);
    double g;
    g = a-b;
    if(g < 0.0)
    {
      return false;
    }
    double t = (-DdEmC-sqrt(g))/(Ddot);
    glm::vec3 point = E + D*((float)t);
    glm::vec3 normal = glm::normalize(point - C);
    record.setT(t);
    record.setPoint(point);
    record.setNormal(normal);
    record.setMatIndex(mat_Index);
    return true;
    };
};
#endif
