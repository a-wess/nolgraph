#ifndef _CLASS_SPHERE_
#define _CLASS_SPHERE_
#include "../types.hpp"

class Sphere : public ISurface {
public:
  Sphere(const vec3<float>& position, const float radius, Material* _material) :
    r(radius),
    pos(position),
    material(_material)
  {};
  Intersection intersect(const Ray& ray) {
    Intersection res;
    vec3<float> o = ray.origin - pos;
    float DO = ray.dir.dot(o);
    float D = 4 * DO * DO - 4 * (o.dot(o) - r * r);
    if (D >= 0) {
      float t1 = (-2 * DO + sqrt(D))/2.0f;
      float t2 = (-2 * DO - sqrt(D))/2.0f;
      float t = std::min(t1, t2);
      res.hit = true;
      res.distance = (ray.dir * t).value();
      res.position = ray.point_at(t);
      res.surface_normal = res.position - pos;
      res.material = material;
    }
    return res;
  };
private:
  float r;
  vec3<float> pos;
  Material* material;
};

#endif
