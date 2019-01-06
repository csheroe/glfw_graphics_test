#ifndef CAMERA_H
#define CAMERA_H
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

class Camera
{
  private:
    glm::vec3 eye = glm::vec3(0,0,1);
    glm::vec3 lookAt = glm::vec3(0,0,0);
    glm::vec3 up = glm::vec3(0,1,0);
    float fov = glm::radians(100.0f);
    float nearPlane = 0.1;
    float farPlane = 1000.0;
    float bufferWidth = 500.0;
    float bufferHeight = 500.0;
    glm::mat4 viewMat = glm::mat4();
    glm::mat4 projMat = glm::mat4();
    void recomputeViewMat()
    {
      //recomputes viewMat based on eye, lookAt (center?), and up
      //don't use mat4 , modify class variable not local variable
      viewMat = glm::lookAt(eye, lookAt, up);

    };
    void recomputeProjMat()
    {
      //recomputes projMat based on bufferWidth, bufferHeight, fov, nearPlane, and farPlane
      //aspect ratio = bufferWidth/bufferHeight
      //don't use mat4 , modify class variable not local variable
      float aspectRatio =  ((float) bufferWidth)/ ((float) bufferHeight);
      projMat = glm::perspective(fov,aspectRatio,nearPlane,farPlane);
    };
  public:
    Camera(glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, float fov,
    float nearPlane, float farPlane, int bufferWidth, int bufferHeight)
    {
      //this -> everything
      this -> eye = eye;
      this -> lookAt = lookAt;
      this -> up = up;
      this -> fov = fov;
      this -> nearPlane = nearPlane;
      this -> farPlane = farPlane;
      this -> bufferWidth = bufferWidth;
      this -> bufferHeight = bufferHeight;
      //set appropriate values and calls recomputeViewMat and recomputeProjMat
      recomputeViewMat();
      recomputeProjMat();
    };
    void updateBufferSize(int width, int height)
    {
      bufferWidth=width;
      bufferHeight=height;
      recomputeProjMat();
    };
    glm::mat4 getViewMatrix()
    {
      return viewMat;
    };
    glm::mat4 getProjectionMatrix()
    {
      return projMat;
    };
    void rotateRight(float angle)
    {
      lookAt = glm::vec3(glm::translate(eye) * glm::rotate(angle,up) * glm::translate(-eye) *
       glm::vec4(lookAt,1));
       recomputeViewMat();

    };
    void rotateUp(float angle)
    {
      glm::vec3 forward = glm::normalize(lookAt - eye);
      glm::vec3 right = glm::normalize(glm::cross(forward, up));
      lookAt = glm::vec3(glm::translate(eye) * glm::rotate(angle,right) * glm::translate(-eye) *
       glm::vec4(lookAt,1));
       recomputeViewMat();

    };
    void forward(float distance)
    {
      //float distance;
      glm::vec3 forward = distance * (glm::normalize(lookAt - eye));
      lookAt =  glm::vec3(glm::translate(forward) * glm::vec4(lookAt,1));
      eye =  glm::vec3(glm::translate(forward) * glm::vec4(eye,1));
      recomputeViewMat();


    };
    void strafeRight(float distance)
    {
      glm::vec3 forward = glm::normalize(lookAt - eye);
      glm::vec3 right = distance * (glm::normalize(glm::cross(forward, up)));
      //transform by translating?
      lookAt =  glm::vec3(glm::translate(right) * glm::vec4(lookAt,1));
      eye =  glm::vec3(glm::translate(right) * glm::vec4(eye,1));
      recomputeViewMat();
    };
};
#endif
