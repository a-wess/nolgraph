#ifndef _RAYS_VOLUMES_
#define _RAYS_VOLUMES_
#include <primitives/types.hpp>
#include <math/vec3.hpp>

class BBox {
public:
  BBox(const vec3<float> &_p1, const vec3<float> &_p2) : p1(_p1), p2(_p2) {

  };
  bool hit(const Ray& ray);
private:
  vec3<float> p1, p2;
};

#endif
