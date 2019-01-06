#ifndef MESHMATERIAL_H
#define MESHMATERIAL_H
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
#include "glm/gtx/transform.hpp"
#include <cstring>
#include <sstream>

using namespace std;

class MeshMaterial
{
  private:
    glm::vec3 kd = glm::vec3(1,1,1);
    glm::vec3 ks = glm::vec3(0,0,0);
    float shiny = 1.0;
  public:
    MeshMaterial()
    {
    };
    float getShininess()
    {
    return shiny;
    };
    glm::vec3 getKd()
    {
    return kd;
    };
    glm::vec3 getKs()
    {
    return ks;
    };
    void setShininess(float value)
    {
    shiny = value;
    };
    void setKd(glm::vec3 value)
    {
    kd = value;
    };
    void setKs(glm::vec3 value)
    {
    ks = value;
    };
};
#endif
