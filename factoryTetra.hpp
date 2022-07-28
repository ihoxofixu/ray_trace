#ifndef FACTORY_TETRA_HPP_INCLUDED
#define FACTORY_TETRA_HPP_INCLUDED

#include "factory.hpp"
#include "tetrahedron.hpp"

namespace raytrace{

class FactoryTetra : public Factory {
public:
  virtual Object* Create(std::vector<float>& values) const override final{
    if (values.size() == 12){
      return new Tetra(vec3f(values[0], values[1], values[2]), vec3f(values[3], values[4], values[5]),
                     vec3f(values[6], values[7], values[8]), vec3f(values[9], values[10], values[11]));
    }
    else{
      std::cout << "ERROR: wrong amount of values to create a tetrahedron\n";
      return new Tetra(vec3f(0, 0, 0), vec3f(0, 0, 0), vec3f(0, 0, 0), vec3f(0, 0, 0));
    }
  }

  FactoryTetra() = default;
  virtual ~FactoryTetra() = default;
};

}

#endif
