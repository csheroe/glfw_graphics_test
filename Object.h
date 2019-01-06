#ifndef OBJECT_H
#define OBJECT_H
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
#include "Model.h"
#include "MeshShader.h"

using namespace std;

class Object
{
  private:
  Model *model = NULL;
  glm::mat4 modelMat;
  glm::vec4 center = glm::vec4(0,0,0,1);
  public:
  Object()
  {
  //does nothing
  };
  void setModel(Model *m)
  {
  model = m;
  };
  void translate(glm::vec3 t)
  {
  glm::mat4 M = glm::translate(t);
  modelMat = M*modelMat;
  center = M*center;
  };
  void rotate(float angle, glm::vec3 axis)
  {
    modelMat = glm::translate(glm::vec3(center)) * glm::rotate(angle,axis) * glm::translate(-glm::vec3(center))
    *modelMat;
  };
  void scale(glm::vec3 s)
  {
    modelMat = glm::translate(glm::vec3(center)) * glm::scale(s)/*scale by s*/ * glm::translate(-glm::vec3(center))
    *modelMat;
  };
  void draw(MeshShader *shader)
  {
    if (model != NULL)
    {
      shader -> setModelTransform(modelMat);
      model -> draw();
      // call setModelTransform(modelMat) on shader
      //call draw() on model
    }
  };
  void resetTransformations()
  {
    modelMat = glm::mat4(); //set to identity matrix
    center = glm::vec4(0,0,0,1);
  };
};
#endif
