#ifndef MATERIAL_H
#define MATERIAL_H
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

using namespace std;

class Material
{
private:
  glm::vec3 Color=glm::vec3(1,1,1);
  float Kd = 1;
  float Ks = 0;
  float Shininess=1;
  float Transmittance=0;
  float IndexRefraction=1;
public:
  Material()
  {
  };
  glm::vec3 getColor()
  {
    return Color;
  };
  float getKd()
  {
    return Kd;
  };
  float getKs()
  {
    return Ks;
  };
  float getShine()
  {
    return Shininess;
  };
  float getTransmittance()
  {
    return Transmittance;
  };
  float getIndexRefraction()
  {
    return IndexRefraction;
  };
  void read(string data) /*expects a string "f red green blue Kd Ks
  shininess transmittance refraction"*/
  {
    stringstream ss(data);
    char dummy[80];
    ss >> dummy;
    ss>>Color.r>>Color.g>>Color.b;
    ss>>Kd>>Ks>>Shininess>>Transmittance>>IndexRefraction;

  };
  string toString()
  {
  //returns string with read (above) format
  string out;
  out += "f "+to_string(Color.r)+" "+to_string(Color.g)+" "+to_string(Color.b)+
  " "+to_string(Kd)+" "+to_string(Ks)+" "+to_string(Shininess)+" "
  +to_string(Transmittance)+" "+to_string(IndexRefraction);
  return out;
  };
};
#endif
