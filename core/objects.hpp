#pragma once
#include "math/math.hpp"

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
