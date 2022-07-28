#ifndef TETRAHEDRON_CPP
#define TETRAHEDRON_CPP

#include "tetrahedron.hpp"

namespace raytrace{

vec3f Tetra::get_center(){
  if (this->get_params().size() != 0){
    return (this->get_params()[0] + this->get_params()[1] + this->get_params()[2] + this->get_params()[3]) / 4;
  }
  else{
    std::cout << "ERROR: params not defined, (0, 0, 0) returned\n";
    return vec3f();
  }
}


void Tetra::output(){
  for (auto i: this->get_params()){
    i.output();
  }
}


bool Tetra::side_has(int i1, int i2, int i3, const vec3f& point){
  vec3f v1 = this->get_params()[i1];
  vec3f v2 = this->get_params()[i2];
  vec3f v3 = this->get_params()[i3];
  float cosphi1 = dot((point - v1).normalized(), (v3 - v1).normalized()),
        sinphi1 = cross((point - v1).normalized(), (v3 - v1).normalized()).magnitute(),
        costheta1 = dot((v2 - v1).normalized(), (v3 - v1).normalized()),
        sintheta1 = cross((v2 - v1).normalized(), (v3 - v1).normalized()).magnitute();
  float cosphi2 = dot((point - v2).normalized(), (v1 - v2).normalized()),
        sinphi2 = cross((point - v2).normalized(), (v1 - v2).normalized()).magnitute(),
        costheta2 = dot((v3 - v2).normalized(), (v1 - v2).normalized()),
        sintheta2 = cross((v3 - v2).normalized(), (v1 - v2).normalized()).magnitute();
  float cosphi3 = dot((point - v3).normalized(), (v2 - v3).normalized()),
        sinphi3 = cross((point - v3).normalized(), (v2 - v3).normalized()).magnitute(),
        costheta3 = dot((v1 - v3).normalized(), (v2 - v3).normalized()),
        sintheta3 = cross((v1 - v3).normalized(), (v2 - v3).normalized()).magnitute();
  bool answer = (cosphi1 - costheta1 > 0 && sinphi1 * sintheta1 > 0) &&
                (cosphi2 - costheta2 > 0 && sinphi2 * sintheta2 > 0) &&
                (cosphi3 - costheta3 > 0 && sinphi3 * sintheta3 > 0) &&
                (fabs(dot(point - v1, cross(v2 - v1, v3 - v1))) < 1e-5);
  return answer;
}


vec3f Tetra::normal_to_surface(const vec3f& intersection){
  if (this->side_has(0, 1, 2, intersection)){
    vec3f norm = cross((this->get_params()[1] - this->get_params()[0]), (this->get_params()[2] - this->get_params()[0])).normalized();
    vec3f tmp = intersection - this->get_params()[3];
    if (dot(tmp, norm) < 0){
      norm *= -1;
    }
    return norm;
  }
  else if (this->side_has(0, 1, 3, intersection)){
    vec3f norm = cross((this->get_params()[1] - this->get_params()[0]), (this->get_params()[3] - this->get_params()[0])).normalized();
    vec3f tmp = intersection - this->get_params()[2];
    if (dot(tmp, norm) < 0){
      norm *= -1;
    }
    return norm;
  }
  else if (this->side_has(0, 2, 3, intersection)){
    vec3f norm = cross((this->get_params()[3] - this->get_params()[0]), (this->get_params()[2] - this->get_params()[0])).normalized();
    vec3f tmp = intersection - this->get_params()[1];
    if (dot(tmp, norm) < 0){
      norm *= -1;
    }
    return norm;
  }
  else if (this->side_has(1, 2, 3, intersection)){
    vec3f norm = cross((this->get_params()[3] - this->get_params()[1]), (this->get_params()[2] - this->get_params()[1])).normalized();
    vec3f tmp = intersection - this->get_params()[0];
    if (dot(tmp, norm) < 0){
      norm *= -1;
    }
    return norm;
  }
  std::cout << "ERROR: intersection does not belong to Tetrahedron, (0, 0, 0) returned\n";
  return vec3f(0, 0, 0);
}


void Tetra::add_t(const vec3f& ray_origin, const vec3f& ray_direction, int i1, int i2, int i3, std::vector<float>& possible_t){
  vec3f norm = cross(this->get_params()[i2] - this->get_params()[i1], this->get_params()[i3] - this->get_params()[i1]);
  if (fabs(dot(ray_direction, norm)) > 1e-5){
    float t1 = dot(this->get_params()[i1] - ray_origin, norm) / dot(ray_direction, norm);
    vec3f inters1 = ray_origin + ray_direction * t1;
    if (this->side_has(i1, i2, i3, inters1) && t1 > 0){
          possible_t.push_back(t1);
    }
  }
}


float Tetra::to_intersection(const vec3f& ray_origin, const vec3f& ray_direction){
  std::vector<float> possible_t = {};

  this->add_t(ray_origin, ray_direction, 0, 1, 2, possible_t);
  this->add_t(ray_origin, ray_direction, 0, 1, 3, possible_t);
  this->add_t(ray_origin, ray_direction, 0, 2, 3, possible_t);
  this->add_t(ray_origin, ray_direction, 1, 2, 3, possible_t);

  if (possible_t.size() > 0){
    float mini = -1;
    for (auto t: possible_t){
      if (mini < 0 || t < mini){
        mini = t;
      }
    }
    return mini;
  }
  return -1;
}

} //namespace raytrace

#endif
