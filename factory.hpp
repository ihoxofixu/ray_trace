#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

#include <vector>
#include "vecmath.hpp"
#include "object.hpp"

namespace raytrace{

class Factory {
public:
  virtual Object* Create(std::vector<float>& values) const = 0;

  Factory() = default;
  virtual ~Factory() = default;
};

}

#endif
