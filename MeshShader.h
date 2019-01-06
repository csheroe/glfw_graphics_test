#ifndef MESHSHADER_H
#define MESHSHADER_H
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
#include "Shader.h"
#include "MeshMaterial.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

class MeshShader : public Shader
{
  private:
    GLint modelMatLoc = -1;
    GLint viewMatLoc = -1;
    GLint normalMatLoc = -1;
    GLint projMatLoc = -1;
    GLint shinyLoc = -1;
    GLint kdLoc = -1;
    GLint ksLoc = -1;
    GLint lightPosLoc = -1;
    GLint lightColorLoc = -1;
    glm::mat4 modelMat;
    glm::mat4 viewMat;
  public:
    MeshShader(string vertexFilename, string fragmentFilename):
    Shader(vertexFilename, fragmentFilename)
    {
    modelMatLoc =  glGetUniformLocation( programID, "modelMat");
    viewMatLoc =   glGetUniformLocation( programID, "viewMat" );
    normalMatLoc =   glGetUniformLocation( programID, "normalMat" );
    projMatLoc =  glGetUniformLocation( programID, "projMat" );
    shinyLoc =  glGetUniformLocation( programID, "material.shininess" );
    kdLoc =   glGetUniformLocation( programID, "material.kd" );
    ksLoc  = glGetUniformLocation( programID, "material.ks" );
    lightPosLoc =  glGetUniformLocation( programID, "light.pos" );
    lightColorLoc =  glGetUniformLocation( programID, "light.color" );
    };
    void setModelTransform(glm::mat4 &modelMat)
    {
      this -> modelMat = modelMat;
      glm::mat4 normalMat = glm::transpose(glm::inverse(viewMat*modelMat));
      //pass in modelMat and normalMat to the shader program
      glUniformMatrix4fv(	modelMatLoc, 1, GL_FALSE,
  		glm::value_ptr(modelMat));
      glUniformMatrix4fv(	normalMatLoc, 1, GL_FALSE,
  		glm::value_ptr(normalMat));
    };
    void setViewAndProjection(Camera *camera)
    {
     this -> viewMat = camera -> getViewMatrix();
      glm::mat4 normalMat = glm::transpose(glm::inverse(viewMat*modelMat));
      //pass to shader
      glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE,
  		glm::value_ptr(viewMat));
      glUniformMatrix4fv(projMatLoc, 1, GL_FALSE,
  		glm::value_ptr(camera->getProjectionMatrix()));
      glUniformMatrix4fv(normalMatLoc	, 1, GL_FALSE,
  		glm::value_ptr(normalMat));
    };
    void setMaterial(MeshMaterial *material)
    {
      //pass in shininess to shader
      glUniform1f(shinyLoc,material -> getShininess());
      glUniform3fv(kdLoc, 1,glm::value_ptr(material -> getKd() ));
      glUniform3fv(ksLoc, 1,glm::value_ptr(material -> getKs()));

    };
    void setLight(Light *light)
    {
      glUniform3fv(lightPosLoc, 1, glm::value_ptr(light -> getPos()));
      glUniform3fv(lightColorLoc, 1,glm::value_ptr(light -> getColor()) );
    };
};
#endif
