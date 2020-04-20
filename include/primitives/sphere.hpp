#ifndef _RAYS_SPHERE_
#define _RAYS_SPHERE_

#include <primitives/types.hpp>

class Sphere: public I_surface {
public:
  Sphere(const vec3<float>& o, float r, int m): origin(o), radius(r), material_idx(m) {};
  float intersect(const Ray& r) {
    const auto D = r.origin - origin;
    float a = r.dir.value() * r.dir.value();
    float b = 2 * D.dot(r.dir);
    float c = D.value() * D.value() - radius * radius;
    float discr = b*b - 4*a*c;

    return discr ? (-b - sqrt(discr))/(2*a) : INFINITY;
  };
  vec3<float> normal_at(const vec3<float>& p) {
    return (p - origin).norm();
  };
  int get_material_idx() { return material_idx; }
private:
  vec3<float> origin;
  float radius;
  int material_idx;
};

#endif