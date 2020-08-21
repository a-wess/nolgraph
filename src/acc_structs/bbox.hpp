#ifndef _RAYS_BBOX_
#define _RAYS_BBOX_
#include <core/types.hpp>
#include <math/vec3.hpp>

struct BBox {
  BBox()
      : mn(INFINITY, INFINITY, INFINITY), mx(-INFINITY, -INFINITY, -INFINITY){};
  BBox(const vec3<float> &_min, const vec3<float> &_max) : mn(_min), mx(_max){};
  Intersection intersect(const Ray &ray);
  Intersection debug(const Ray &ray);
  void expand(const BBox &box);
  void expand(const vec3<float> &point);
  int maximum_extent();
  float area();
  vec3<float> mn, mx;
};

#endif
