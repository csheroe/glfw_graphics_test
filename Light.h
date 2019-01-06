#ifndef LIGHT_H
#define LIGHT_H
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

class Light
{
  private:
    glm::vec3 position=glm::vec3(0,0,0);
    glm::vec3 color=glm::vec3(1,1,1);
  public:
    Light()
    {
    };
    Light(glm::vec3 pos)
    {
    position=pos;
    };
    Light(glm::vec3 pos,glm::vec3 color)
    {
    position=pos;
    this -> color=color;
    };

    glm::vec3 getPos()
    {
    return position;
    };
    glm::vec3 getColor()
    {
    return color;
    };
    void read (string data)
    {
      stringstream ss(data);
      char dummy[80];
      ss >> dummy;
      ss >> position.x >> position.y >> position.z;

      if (ss >> color.r)
      {
      ss >> color.g >> color.b;
      }
      else
      {
      color=glm::vec3(1,1,1);
      }

    };
     /*expects a string with the following format;
    l x y z r g b OR l x y z */
    string toString()
    {
    string output= "l ";
    output += to_string(position.x)+" ";
    output += to_string(position.y)+" ";
    output += to_string(position.z)+" ";
    output += to_string(color.r)+" ";
    output += to_string(color.g)+" ";
    output += to_string(color.b);
    return output;
    };
    /*returns a string with the following format;
    l x y z r g b */
};
#endif
