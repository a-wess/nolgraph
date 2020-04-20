#ifndef _RAYS_GLTF_
#define _RAYS_GLTF_

#include <math/vec3.hpp>
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <assert.h>

namespace GLTF {
  void GLB_parse(std::string_view file_name);
};

#endif