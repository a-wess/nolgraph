#pragma once
#include <math.hpp>

struct Ray {
  vec3<float> origin;
  float t;
};

class I_intersect {
public:
  virtual float intersect(const Ray& r) = 0;
};
