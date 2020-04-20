#ifndef _RAYS_TYPES_
#define _RAYS_TYPES_

#include <math/vec3.hpp>

struct Ray {
  vec3<float> origin;
  vec3<float> dir;
  vec3<float> point_at(float t) const { return origin + dir * t; };
};


class I_surface {
public:
  virtual float intersect(const Ray& r) = 0;
  virtual vec3<float> normal_at(const vec3<float>& p) = 0;
  virtual int get_material_idx() = 0;
};

#endif
