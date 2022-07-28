#ifndef VECMATH_CPP
#define VECMATH_CPP

#include "vecmath.hpp"

namespace raytrace{

vec3f cross(const vec3f& u, const vec3f& v){
  return vec3f(u.getY() * v.getZ() - u.getZ() * v.getY(),
               u.getZ() * v.getX() - u.getX() * v.getZ(),
               u.getX() * v.getY() - u.getY() * v.getX());
}


float dot(const vec3f& u, const vec3f& v){
  return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}


vec3f operator * (float k, const vec3f& v){
  return v * k;
}


vec3f vecround(const vec3f& v){
  return vec3f(round(v.getX()), round(v.getY()), round(v.getZ()));
}

} //namespace raytrace

#endif
