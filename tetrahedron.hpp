#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include <iostream>
#include "object.hpp"

namespace raytrace{

class Tetra final : public Object {
public:
  Tetra() : Object() {};


  Tetra(const vec3f v1, const vec3f v2, const vec3f v3, const vec3f v4) : Object(std::vector<vec3f>{v1, v2, v3, v4}) {};


  Tetra(std::vector<vec3f> params_) : Object(params_) {};


  virtual vec3f get_center() override final;


  virtual void output() override final;


  bool side_has(int i1, int i2, int i3, const vec3f& point);


  virtual vec3f normal_to_surface(const vec3f& intersection) override final;


  void add_t(const vec3f& ray_origin, const vec3f& ray_direction, int i1, int i2, int i3, std::vector<float>& possible_t);


  virtual float to_intersection(const vec3f& ray_origin, const vec3f& ray_direction) override final;

};

} //namespace raytrace

#endif
