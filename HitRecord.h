#ifndef HITRECORD_H
#define HITRECORD_H
#define MIN_DISTANCE_T 0.001
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
#include "Material.h"
#include "Light.h"
#include "Sphere.h"

using namespace std;

class HitRecord
{
private:
  double t = -1;
  glm::vec3 intersection=glm::vec3(0,0,0);
  glm::vec3 normal=glm::vec3(0,0,1);
  int MatIndexAtIntersection=0; 
public:
  HitRecord()
  {

  };
  HitRecord(double t, glm::vec3 point, glm::vec3 normal, int matIndex)
  {
    this ->t=t;
    this ->intersection=point;
    this ->normal=normal;
    this ->MatIndexAtIntersection=matIndex;
  };
  double getT()
  {
  return t;
  };
  glm::vec3 getPoint()
  {
  return intersection;
  };
  glm::vec3 getNormal()
  {
  return normal;
  };
  int getMatIndex()
  {
  return MatIndexAtIntersection;
  };
  void setT(double t)
  {
  this ->t=t;
  };
  void setPoint(glm::vec3 point)
  {
  this ->intersection=point;
  };
  void setNormal(glm::vec3 normal)
  {
  this ->normal=normal;
  };
  void setMatIndex(int index)
  {
  this ->MatIndexAtIntersection=index;
  };

};
#endif
