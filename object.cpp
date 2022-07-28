#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "object.hpp"

namespace raytrace{

Object* nearest_object(std::vector<Object*> objects, vec3f ray_origin, vec3f ray_direction){
  Object* nearest_obj = NULL;
  float min_distance = -1;
  for (auto curr_obj: objects){
    float curr_distance = curr_obj->to_intersection(ray_origin, ray_direction);
    if (min_distance == -1 || curr_distance > 0 && curr_distance < min_distance){
      nearest_obj = curr_obj;
      min_distance = curr_distance;
    }
  }
  if (min_distance > 0){
    return nearest_obj;
  }
  else{
    return NULL;
  }
}

} //namespace raytrace


#endif
