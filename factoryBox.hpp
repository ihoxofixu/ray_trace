#ifndef FACTORY_BOX_HPP_INCLUDED
#define FACTORY_BOX_HPP_INCLUDED

#include "factory.hpp"
#include "box.hpp"

namespace raytrace{

class FactoryBox : public Factory {
public:
  virtual Object* Create(std::vector<float>& values) const override final{
    if (values.size() == 6){
      if (values[0] < values[3]){
        return new Box(vec3f(values[0], values[1], values[2]), vec3f(values[3], values[4], values[5]));
      }
      else{
        return new Box(vec3f(values[3], values[4], values[5]), vec3f(values[0], values[1], values[2]));
      }
    }
    else{
      std::cout << "ERROR: wrong amount of values to create a box\n";
      return new Box(vec3f(0, 0, 0), vec3f(0, 0, 0));
    }
  }

  FactoryBox() = default;
  virtual ~FactoryBox() = default;
};

}

#endif
