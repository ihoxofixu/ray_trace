#ifndef VECMATH_HPP
#define VECMATH_HPP

#include <cmath>
#include <iostream>
#include "vec3.hpp"

namespace raytrace{

vec3f cross(const vec3f& u, const vec3f& v);


float dot(const vec3f& u, const vec3f& v);


vec3f operator * (float k, const vec3f& v);

vec3f vecround(const vec3f& v);

} //namespace raytrace

#endif
