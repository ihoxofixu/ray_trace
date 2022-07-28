#ifndef FACTORY_SPHERE_HPP_INCLUDED
#define FACTORY_SPHERE_HPP_INCLUDED

#include "factory.hpp"
#include "sphere.hpp"

namespace raytrace{

class FactorySphere : public Factory {
public:
  virtual Object* Create(std::vector<float>& values) const override final{
    if (values.size() == 4){
      return new Sphere(values[3], vec3f(values[0], values[1], values[2]));
    }
    else{
      std::cout << "ERROR: wrong amount of values to create a sphere\n";
      return new Sphere(0, vec3f(0, 0, 0));
    }
  }

  FactorySphere() = default;
  virtual ~FactorySphere() = default;
};

}

#endif
