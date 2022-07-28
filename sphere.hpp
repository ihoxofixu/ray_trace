#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>
#include "object.hpp"

namespace raytrace{

class Sphere final : public Object {
private:
  float radius = 0;
public:
  Sphere() : Object() {};


  Sphere(float radius_, const vec3f center) : Object(1, &center) {
    radius = radius_;
  };


  Sphere(std::vector<vec3f> params_) : Object(params_) {};

  float get_radius(){
    return radius;
  }


  virtual vec3f get_center() override final;


  virtual void output() override final;


  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) override final;


  virtual vec3f normal_to_surface(const vec3f& intersection) override final;

};

} //namespace raytrace

#endif
