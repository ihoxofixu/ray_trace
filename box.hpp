#ifndef BOX_HPP
#define BOX_HPP

#include <iostream>
#include "object.hpp"

namespace raytrace{

class Box final : public Object {
public:
  Box() : Object() {};


  Box(const vec3f first, const vec3f second) : Object(std::vector<vec3f>{first, second}) {};


  Box(std::vector<vec3f>& params_) : Object(params_) {};


  virtual vec3f get_center() override final;


  virtual void output() override final;


  bool has(const vec3f& point);


  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) override final;


  virtual vec3f normal_to_surface(const vec3f& intersection) override final;

};

} //namespace raytrace

#endif
