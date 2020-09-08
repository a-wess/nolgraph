#ifndef _RAYS_QUAD_
#define _RAYS_QUAD_

#include <acc_structs/bbox.hpp>
#include <acc_structs/primitive.hpp>
#include <math/vec4.hpp>
#include <memory>
#include <vector>

#include "../mesh.hpp"
#include "../types.hpp"

class Quad : public Primitive {
public:
  Quad(int _offset, Mesh *_mesh, Material *_material) : offset(_offset), mesh(_mesh), material(_material){};
  Intersection intersect(const Ray &ray);
  BBox get_bbox();
private:
  int offset;
  vec4<int> get_indices() {
    return vec4<int>(mesh->indices[offset], mesh->indices[offset + 1],
                     mesh->indices[offset + 2], mesh->indices[offset + 3]);
  }
  Mesh *mesh;
  Material *material;
};

#endif
