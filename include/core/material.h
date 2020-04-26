#ifndef _RAYS_MATERIALS_
#define _RAYS_MATERIALS_
#include <math/vec3.hpp>

struct Cheap_material {
  vec3<float> diffuse;
  float specular_coef;
  float diffuse_coef;
};

#endif
