#ifndef _RAYS_TRIANGLE_
#define _RAYS_TRIANGLE_

#include <acc_structs/bbox.hpp>
#include <memory>
#include <vector>

#include "mesh.hpp"
#include "types.hpp"

const float EPSILON = 1e-7;

class Triangle : public ISurface {
public:
  Triangle(int _offset, Mesh *_mesh) : offset(_offset), mesh(_mesh){};
  Intersection intersect(const Ray &ray);
  BBox get_bbox();
  vec3<int> get_indices() {
    return vec3<int>(mesh->indices[offset], mesh->indices[offset + 1],
                     mesh->indices[offset + 2]);
  }
  Mesh *mesh;

private:
  int offset;
};

#endif
