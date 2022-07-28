#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vecmath.hpp"
#include <vector>
#include "omp.h"

namespace raytrace{

class Object{
private:
  std::vector<vec3f> params = {};
  rgb ambient = rgb(0, 0, 0.1);
  rgb diffuse = rgb(0, 0, 0.7);
  rgb specular = rgb(1, 1, 1);
public:
  Object(){}


  Object(int amount, const vec3f* params_){
    for (int i = 0; i < amount; i++){
      params.push_back(params_[i]);
    }
  }


  Object(std::vector<vec3f> params_){
    for (auto i: params_){
      params.push_back(i);
    }
  }


  void set_color(rgb color){
    ambient = color;
    diffuse = color * 6;
  }


  std::vector<vec3f> get_params(){
    return params;
  }


  rgb get_ambient(){
    return ambient;
  }


  rgb get_diffuse(){
    return diffuse;
  }


  rgb get_specular(){
    return specular;
  }


  virtual void output() = 0;


  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) = 0;


  virtual vec3f get_center() = 0;


  virtual vec3f normal_to_surface(const vec3f& intersection) = 0;

};

Object* nearest_object(std::vector<Object*> objects, vec3f ray_origin, vec3f ray_direction);

} //namespace raytrace


#endif
