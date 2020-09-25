#ifndef _RAYS_TYPES_
#define _RAYS_TYPES_

#include <math/vec3.hpp>
#include "material.hpp"

struct Ray {
  vec3<float> origin;
  vec3<float> dir;
  vec3<float> point_at(float t) const { return origin + dir * t; };
};

struct Intersection {
  bool hit = false;
  Material* material;
  float distance = std::numeric_limits<float>::infinity();
  vec3<float> position = {
    std::numeric_limits<float>::infinity(),
    std::numeric_limits<float>::infinity(),
    std::numeric_limits<float>::infinity()
  };
  vec3<float> surface_normal = {0.0f, 0.0f, 0.0f};
};

class ISurface {
public:
  virtual Intersection intersect(const Ray &r) = 0;
};

#endif
