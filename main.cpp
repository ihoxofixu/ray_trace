#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <string>
#include <chrono>
#include "vecmath.hpp"
#include "figures.hpp"
#include "CImg-3.1.0/CImg.h"
#include "omp.h"

using namespace std;
using namespace raytrace;
using namespace cimg_library;

int main(){
  string datafile;
  getline(cin, datafile);
  ifstream fin;
  fin.open(datafile.c_str(), ios::in);

  vec3f camera;
  vec3f light;
  vec3f norm, vert, hor;
  int width, height;
  float dist1, dist2;
  float alpha;

  map<string, Factory*> factoryMap;
  factoryMap["sphere"] = new FactorySphere();
  factoryMap["box"] = new FactoryBox();
  factoryMap["tetra"] = new FactoryTetra();
  vector<Object*> objects = {};

  if (!fin.is_open()){
    cout << "Error! Cannot open file!\n";
    return 1;
  }
  string tmp;
  while (getline(fin, tmp)){
    tmp += " ";
    vector<string> parsed = {};
    string tmp_parse = "";
    for (int i = 0; i < tmp.length(); i++){
      if (tmp.at(i) == ' '){
        parsed.push_back(tmp_parse);
        tmp_parse = "";
      }
      else{
        tmp_parse += tmp[i];
      }
    }
    if (parsed[0] == "cam"){
      camera = vec3f(atof(parsed[1].c_str()), atof(parsed[2].c_str()), atof(parsed[3].c_str()));
    }
    else if (parsed[0] == "norm"){
      norm = vec3f(atof(parsed[1].c_str()), atof(parsed[2].c_str()), atof(parsed[3].c_str()));
    }
    else if (parsed[0] == "up"){
      vert = vec3f(atof(parsed[1].c_str()), atof(parsed[2].c_str()), atof(parsed[3].c_str()));
    }
    else if (parsed[0] == "screen"){
      dist1 = atof(parsed[1].c_str());
    }
    else if (parsed[0] == "limit"){
      dist2 = atof(parsed[1].c_str());
    }
    else if (parsed[0] == "alpha"){
      alpha = atof(parsed[1].c_str());
    }
    else if (parsed[0] == "width"){
      width = atoi(parsed[1].c_str());
    }
    else if (parsed[0] == "height"){
      height = atoi(parsed[1].c_str());
    }
    else if (parsed[0] == "light"){
      light = vec3f(atof(parsed[1].c_str()), atof(parsed[2].c_str()), atof(parsed[3].c_str()));
    }
    else{
      auto curFactory = factoryMap.find(parsed[0]);
      if (curFactory == factoryMap.end()) {
        cout << parsed[0] << endl;
        throw invalid_argument("Error! Wrong type of figure in input file!\n");
      }
      vector <float> vals = {};
      for (int i = 1; i < parsed.size(); i++){
        vals.push_back(atof(parsed[i].c_str()));
      }
      auto curObj = curFactory->second->Create(vals);
      objects.push_back(curObj);
    }
  }

  hor = cross(vert, norm);
  vec3f screen_center = camera + norm * dist1;
  float delta_h = dist1 * tan(alpha * 3.14159265 / 360);
  float delta_w = delta_h * width / height;

  rgb blue(0, 0, 0.1);
  rgb green(0, 0.1, 0);
  float mindist = -1, maxdist = -1;
  for (auto obj: objects){
    float curr_dist = (camera - obj->get_center()).magnitute();
    if (curr_dist > maxdist){
      maxdist = curr_dist;
    }
    if (mindist < 0 || curr_dist < mindist){
      mindist = curr_dist;
    }
  }
  maxdist *= 1.01;
  mindist /= 1.01;
  for (auto obj: objects){
    float curr_dist = (camera - obj->get_center()).magnitute();
    obj->set_color(blue * (maxdist - curr_dist) / (maxdist - mindist) + green * (curr_dist - mindist) / (maxdist - mindist));
  }

  CImg<unsigned char>  theImage_omp(width,height,1,3,0);
  CImg<unsigned char>  theImage(width,height,1,3,0);

  auto start_time = chrono::high_resolution_clock::now();

  #pragma omp parallel for
  for (int i = 0; i < height; i++){
    #pragma omp parallel for
    for (int j = 0; j < width; j++){

      vec3f pixel;
      pixel = screen_center + vert * delta_h * (1 - i * 2.0 / height) + hor * delta_w * ((1 - j * 2.0 / width));

      vec3f direction = (pixel - camera).normalized();
      Object* nearest_obj = nearest_object(objects, camera, direction);
      if (nearest_obj == NULL){
        continue;
      }

      vec3f intersection = camera + nearest_obj->to_intersection(camera, direction) * direction;

      if (dot(intersection, norm) > dist2){
        continue;
      }

      vec3f normal_to_surf = nearest_obj->normal_to_surface(intersection);
      vec3f shifted_point = intersection + 1e-5 * normal_to_surf;
      vec3f intersection_to_light = (light - shifted_point).normalized();
      Object* obstacle = nearest_object(objects, shifted_point, intersection_to_light);

      if (obstacle != NULL){
        continue;
      }

      vec3f illumination(0, 0, 0);
      illumination += nearest_obj->get_ambient();
      illumination += nearest_obj->get_diffuse() * dot(intersection_to_light, normal_to_surf);
      vec3f intersection_to_camera = (camera - intersection).normalized();
      vec3f H = (intersection_to_light + intersection_to_camera).normalized();
      illumination += nearest_obj->get_specular() * pow(dot(normal_to_surf, H), 25);
      illumination.clip(0, 1);
      illumination = vecround(illumination * 255);

      theImage_omp(j,i,0) = illumination.getX();
      theImage_omp(j,i,1) = illumination.getY();
      theImage_omp(j,i,2) = illumination.getZ();
    }
  }

  auto elapsed_time = chrono::high_resolution_clock::now() - start_time;
  long long ns = chrono::duration_cast<chrono::milliseconds>(elapsed_time).count();
  ns = chrono::duration_cast<chrono::milliseconds>(elapsed_time).count();
  cout << "Time consumed with omp: " << ns << "ms" << endl;

  start_time = chrono::high_resolution_clock::now();

  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){

      vec3f pixel;
      pixel = screen_center + vert * delta_h * (1 - i * 2.0 / height) + hor * delta_w * ((1 - j * 2.0 / width));

      vec3f direction = (pixel - camera).normalized();
      Object* nearest_obj = nearest_object(objects, camera, direction);
      if (nearest_obj == NULL){
        continue;
      }

      vec3f intersection = camera + nearest_obj->to_intersection(camera, direction) * direction;

      if (dot(intersection, norm) > dist2){
        continue;
      }

      vec3f normal_to_surf = nearest_obj->normal_to_surface(intersection);
      vec3f shifted_point = intersection + 1e-5 * normal_to_surf;
      vec3f intersection_to_light = (light - shifted_point).normalized();
      Object* obstacle = nearest_object(objects, shifted_point, intersection_to_light);

      if (obstacle != NULL){
        continue;
      }

      vec3f illumination(0, 0, 0);
      illumination += nearest_obj->get_ambient();
      illumination += nearest_obj->get_diffuse() * dot(intersection_to_light, normal_to_surf);
      vec3f intersection_to_camera = (camera - intersection).normalized();
      vec3f H = (intersection_to_light + intersection_to_camera).normalized();
      illumination += nearest_obj->get_specular() * pow(dot(normal_to_surf, H), 25);
      illumination.clip(0, 1);
      illumination = vecround(illumination * 255);

      theImage(j,i,0) = illumination.getX();
      theImage(j,i,1) = illumination.getY();
      theImage(j,i,2) = illumination.getZ();
    }
  }

  elapsed_time = chrono::high_resolution_clock::now() - start_time;
  ns = chrono::duration_cast<chrono::milliseconds>(elapsed_time).count();
  ns = chrono::duration_cast<chrono::milliseconds>(elapsed_time).count();
  cout << "Time consumed without omp: " << ns << "ms" << endl;

  CImgDisplay main_disp(theImage_omp); // display it
  theImage_omp.save_bmp("output.bmp"); // write it
  std::cin.ignore();

  return 0;
}

#endif
