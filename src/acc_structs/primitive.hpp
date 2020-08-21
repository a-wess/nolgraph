#ifndef _RAYS_VOLUMES_
#define _RAYS_VOLUMES_

#include <core/triangle.hpp>
#include <core/types.hpp>
#include <math/vec3.hpp>

#include "bbox.hpp"

struct PrimitiveInfo {
  PrimitiveInfo(Triangle *triangle)
      : t_ptr(triangle), box(triangle->get_bbox()) {
    center = (box.mn + box.mx) / 2;
  };
  Triangle *t_ptr;
  BBox box;
  vec3<float> center;
};

#endif
