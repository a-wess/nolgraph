#ifndef _CLASS_SPHERE_
#define _CLASS_SPHERE_
#include "../types.hpp"

class Sphere : public ISurface {
public:
  Sphere(const vec3<float>& position, const float radius) : r(radius), pos(position) {};
  Intersection intersect() {

  };
private:
  float r;
  vec3<float> pos;
};

#endif
