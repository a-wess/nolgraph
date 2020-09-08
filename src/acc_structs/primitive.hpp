#ifndef _RAYS_VOLUMES_
#define _RAYS_VOLUMES_

#include <core/types.hpp>
#include <math/vec3.hpp>
#include <memory>

#include "bbox.hpp"

struct Primitive: public ISurface {
  virtual Intersection intersect(const Ray& ray) = 0;
  virtual BBox get_bbox() = 0;
  virtual ~Primitive() = 0;
};

struct PrimitiveInfo {
  PrimitiveInfo(Primitive *primitive) : p_ptr(primitive), box(primitive->get_bbox()) {
    center = (box.mn + box.mx) / 2;
  };
  std::unique_ptr<Primitive> p_ptr;
  BBox box;
  vec3<float> center;
};

#endif
