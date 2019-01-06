#ifndef SCENE_H
#define SCENE_H
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
#include "HitRecord.h"

using namespace std;

class Scene
{
private:
  vector<Light*> all_lights;
  vector<Material*> all_materials;
  vector<Sphere*> all_spheres;
  float* imageBuffer = NULL;
  int BufferWidth = 0;
  int BufferHeight= 0;
  glm::vec3 background=glm::vec3(0,0,0);
  void cleanup()
  {
    for(int i=0;i<all_lights.size();i++)
    {
      delete all_lights.at(i);
    }
    all_lights.clear();
    for(int i=0;i<all_spheres.size();i++)
    {
      delete all_spheres.at(i);
    }
    all_spheres.clear();
    for(int i=0;i<all_materials.size();i++)
    {
      delete all_materials.at(i);
    }
    all_materials.clear();
    if(imageBuffer != NULL)
    {
      delete [] imageBuffer; /*I sense that "delete imageBuffer"
       won't actually clear the variable, but I'm just leaving this here for now*/
      imageBuffer = NULL;
    };
  };
public:
  Scene()
  {
  };
  ~Scene()
  {
    cleanup();
  };
  int getLightCnt()
  {
    return all_lights.size();
  };
  int getSurfaceCnt()
  {
    return all_spheres.size();
  };

  int getMaterialCnt()
  {
    return all_materials.size();
  };

  float* getImageBuffer()
  {
    return imageBuffer;
  };

  int getBufferWidth()
  {
    return BufferWidth;
  };

  int getBufferHeight()
  {
    return BufferHeight;
  };

  string toString() /*expects a string with the format
  b red green blue + "\n"*/
  {
    string stringout;
    stringout += "b "+to_string(background.r)+" "+to_string(background.g)+" "+to_string(background.b)+ "\n";
    for(int i=0;i<all_lights.size();i++)
    {
      stringout +=  all_lights.at(i) -> toString()+"\n";
    }
    for(int i=0;i<all_materials.size();i++)
    {
      stringout +=  all_materials.at(i) -> toString()+"\n";
    }
    for(int i=0;i<all_spheres.size();i++)
    {
      stringout +=  all_spheres.at(i) -> toString()+"\n";
    }
    return stringout;
  };


  bool loadNFF(string filename,int WindowWidth,int windowHeight)
  {
    ifstream file(filename);
    if(file.fail())
    {
      cout<<"Error, could not load"<<filename<<endl;
      return false;
    }
    cleanup();
    int currentMatIndex = -1;
    while(!file.eof())
    {
        string line;
        getline(file,line);
        string token;
        stringstream ss(line);
        ss >> token;
        if(token == "l")
        {
          Light* light=new Light();
          light->read(line);
          all_lights.push_back(light);
        }
        else if(token == "s")
        {
          Sphere* sphere=new Sphere();
          sphere->read(line);
          all_spheres.push_back(sphere);
          sphere->setMaterialIndex(currentMatIndex);
        }
        else if(token == "f")
        {
          Material* material=new Material();
          material->read(line);
          all_materials.push_back(material);
          currentMatIndex++;
        }
        else if(token == "b")
        {
          ss >> background.r>>background.g>>background.b;
        }
    }
    file.close();
    BufferWidth = WindowWidth;
    BufferHeight = windowHeight;
    imageBuffer = new float[3 * BufferWidth* BufferHeight]; /*not sure if
    i have to pass imagebuffer into this loadNFF function*/
    return  true;

  };
  void clearImageBuffer(glm::vec3 color)
  {
  int i, j;
  for (i = 0; i < BufferHeight; i++)
    {
      for(j=0; j < BufferWidth; j++)
      {
        imageBuffer[(i*BufferWidth + j)*3] = color.r;
        imageBuffer[(i*BufferWidth + j)*3+1] = color.g;
        imageBuffer[(i*BufferWidth + j)*3+2] = color.b;
      }
    }
  };
  void setPixelinImageBuffer(int x, int y, glm::vec3 color)
  {
  int index = (y*BufferWidth + x) * 3;

  imageBuffer[index]= color.r;
  imageBuffer[index + 1] = color.g;
  imageBuffer[index +2] = color.b;
  };


  bool intersectRayWithScene(glm::vec3 rayStart, glm::vec3 rayDir, double minDist,
  HitRecord &bestRecord)
  {
    bool AnyHit=false;
    for(int i=0;i<all_spheres.size();i++)
    {
      HitRecord TempRecord;
      if(all_spheres.at(i) -> getIntersection(rayStart, rayDir, TempRecord)) //i hit but i dont know where
      {

          if(TempRecord.getT() > minDist) //i hit it really well!
          {
            if(!AnyHit)
            {
            bestRecord=TempRecord;
            AnyHit=true;
            }
            else
            {
              if (TempRecord.getT()<bestRecord.getT())
              {
                bestRecord=TempRecord;
              }
            }
          }
      }
    }
    return AnyHit;
  };
  void raytrace(/*pass in*/)
  {
    clearImageBuffer(glm::vec3(0,0,0));
    double nx = getBufferWidth();
    double ny = getBufferHeight();
    double nearDist = 0;
    double AspectRatio = (nx/ny); //contained in cpp file
    double imagePlaneHeight = 2.0;
    double imagePlaneWidth = imagePlaneHeight * (AspectRatio);
    double left = -(imagePlaneWidth)/2.0;
    double right = imagePlaneWidth/2.0;
    double bottom = -(imagePlaneHeight)/2.0;
    double top = imagePlaneHeight/2.0;
    glm::vec3 U = glm::vec3(1 ,0 ,0 );
    glm::vec3 V = glm::vec3(0 ,1 ,0 );
    glm::vec3 W = glm::vec3(0 ,0 ,1 );
    glm::vec3 E = glm::vec3(0 ,0 ,1.5 );
    float d = 1.0;


    for(int i=0;i<BufferHeight;i++)
    {
      for(int j=0;j<BufferWidth;j++)
        {
          float u = left + (right-left)*(i+0.5)/nx;
          float v = bottom + (top-bottom)*(j+0.5)/ny;
          glm::vec3 rayDir = u*U+v*V-d*W;
          glm::vec3 rayStart = E;
          HitRecord bestRecord;
          if(intersectRayWithScene(rayStart, rayDir, nearDist, bestRecord))
          {
          glm::vec3 color = all_materials.at(bestRecord.getMatIndex()) -> getColor();
          setPixelinImageBuffer(j,i, color);
          }
          else
          {
          setPixelinImageBuffer(j,i, background);          }
        }

    }

  };
};
#endif
