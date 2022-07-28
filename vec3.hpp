#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

namespace raytrace {

class vec3f final
{
private:
  float x = 0;
  float y = 0;
  float z = 0;
public:

  float getX() const{
    return x;
  }


  float getY() const{
    return y;
  }


  float getZ() const{
    return z;
  }


  vec3f(){}


  vec3f(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
  }


  vec3f operator+ (const vec3f& v) const{
    return vec3f(x + v.x, y + v.y, z + v.z);
  }


  vec3f operator- (const vec3f& v) const{
    return vec3f(x - v.x, y - v.y, z - v.z);
  }


  vec3f operator* (float k) const{
    return vec3f(k * x, k * y, k * z);
  }


  vec3f operator/ (float k) const{
    return vec3f(x / k, y / k, z / k);
  }


  vec3f& operator= (const vec3f& v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }


  vec3f& operator+= (const vec3f& v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }


  vec3f& operator*= (float k){
    x *= k;
    y *= k;
    z *= k;
    return *this;
  }


  float magnitute2() const{
    return x * x + y * y + z * z;
  }


  float magnitute() const{
    return std::sqrt(magnitute2());
  }


  void normalize(){
    float magn = magnitute();
    x /= magn; y /= magn; z /= magn;
  }


  vec3f normalized() const{
    float magn = magnitute();
    return vec3f(x / magn, y / magn, z / magn);
  }


  void output(){
    std::cout << x << " " << y << " " << z << "\n";
  }


  void clip(float lower_limit, float upper_limit){
    if (x > upper_limit){
      x = upper_limit;
    }
    else if (x < lower_limit){
      x = lower_limit;
    }
    if (y > upper_limit){
      y = upper_limit;
    }
    else if (y < lower_limit){
      y = lower_limit;
    }
    if (z > upper_limit){
      z = upper_limit;
    }
    else if (z < lower_limit){
      z = lower_limit;
    }
  }

};

  typedef vec3f rgb;

} // namespace raytrace

#endif // VEC3_HPP
