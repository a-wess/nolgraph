#ifndef _RAYS_TYPES_
#define _RAYS_TYPES_

#include <math/vec3.hpp>

struct Ray {
  vec3<float> origin;
  vec3<float> dir;
  vec3<float> point_at(float t) const { return origin + dir * t; };
};

struct Intersection {
  vec3<float> position;
  vec3<float> surface_normal;
};

class I_surface {
public:
  virtual Intersection intersect(const Ray& r) = 0;
};

#endif
