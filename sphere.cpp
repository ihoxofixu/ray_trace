#ifndef SPHERE_CPP
#define SPHERE_CPP

#include "sphere.hpp"

namespace raytrace{

vec3f Sphere::get_center(){
  if (this->get_params().size() != 0){
    return this->get_params()[0];
  }
  else{
    std::cout << "ERROR: params not defined, (0, 0, 0) returned\n";
    return vec3f(0, 0, 0);
  }
}


void Sphere::output(){
  for (auto i: this->get_params()){
    i.output();
  }
  std::cout << radius << "\n";
}


float Sphere::to_intersection(const vec3f& ray_origin, const vec3f& ray_direction){
  float b = 2 * dot(ray_direction, ray_origin - this->get_center());
  float c = (ray_origin - this->get_center()).magnitute2() - this->get_radius() * this->get_radius();
  float delta = b * b - 4 * c;
  if (delta > 0){
    float t1 = (-b + std::sqrt(delta)) / 2;
    float t2 = (-b - std::sqrt(delta)) / 2;
    if (t1 > 0 && t2 > 0){
      return std::min(t1, t2);
    }
  }
  return -1;
}


vec3f Sphere::normal_to_surface(const vec3f& intersection){
  return (intersection - this->get_center()).normalized();
}

} //namespace raytrace

#endif
