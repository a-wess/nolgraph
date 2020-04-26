#ifndef _RAYS_SPHERE_
#define _RAYS_SPHERE_

#include <primitives/types.hpp>

class Sphere: public I_surface {
public:
  Sphere(const vec3<float>& o, float r, int m): origin(o), radius(r), material_idx(m) {};
  Intersection intersect(const Ray& r) {
    Intersection result;
    const auto D = r.origin - origin;
    float a = r.dir.value() * r.dir.value();
    float b = 2 * D.dot(r.dir);
    float c = D.value() * D.value() - radius * radius;
    float discr = b*b - 4*a*c;

    if (discr) {
      result.position = r.point_at((-b - sqrt(discr))/(2 * a));
      result.surface_normal = (result.position - origin).norm();
    } else {
      result.position = { INFINITY, INFINITY, INFINITY };
      result.surface_normal = { 0.0f, 0.0f, 0.0f };
    }

    return result;
  };
private:
  vec3<float> origin;
  float radius;
  int material_idx;
};

#endif
