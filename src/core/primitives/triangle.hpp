#ifndef _RAYS_TRIANGLE_
#define _RAYS_TRIANGLE_

#include <acc_structs/bbox.hpp>
#include <acc_structs/primitive.hpp>
#include <memory>
#include <vector>

#include "../mesh.hpp"
#include "../types.hpp"

const float EPSILON = 1e-7;

class Triangle : public Primitive {
public:
  Triangle(int _offset, Mesh *_mesh, Material *_material) : offset(_offset), mesh(_mesh), material(_material){};
  Intersection intersect(const Ray &ray);
  BBox get_bbox();
private:
  vec3<int> get_indices() {
    return vec3<int>(
      mesh->indices[offset],
      mesh->indices[offset + 1],
      mesh->indices[offset + 2]
    );
  }
  int offset;
  Mesh *mesh;
  Material *material;
};

#endif
