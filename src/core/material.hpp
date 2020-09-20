#ifndef _RAYS_MATERIALS_
#define _RAYS_MATERIALS_
#include <math/vec3.hpp>

struct Material {
  vec3<float> diffuse;
  vec3<float> ambient;
  float specular_coef;
  float diffuse_coef;
  float ambient_coef;
};

#endif