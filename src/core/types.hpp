#ifndef _RAYS_TYPES_
#define _RAYS_TYPES_

#include <math/vec3.hpp>

struct Ray {
  vec3<float> origin;
  vec3<float> dir;
  vec3<float> point_at(float t) const { return origin + dir * t; };
};

struct Intersection {
  bool hit = false;
  unsigned int material_idx = 0;
  float distance = INFINITY;
  vec3<float> position = {INFINITY, INFINITY, INFINITY};
  vec3<float> surface_normal = {0.0f, 0.0f, 0.0f};
};

class ISurface {
public:
  virtual Intersection intersect(const Ray &r) = 0;
};

#endif
