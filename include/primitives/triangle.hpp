#ifndef _RAYS_TRIANGLE_
#define _RAYS_TRIANGLE_

#include "types.hpp"
#include <acc_structs/bbox.hpp>
#include <vector>
#include <memory>

const float EPSILON = 1e-7;
class Triangle;

class TriMesh  {
public:
  TriMesh();
  std::vector<vec3<float>> positions;
  std::vector<vec3<float>> normals;
  std::vector<int> indices;
  int triangles_count;
  std::vector<Triangle> tris;
};

class Triangle : public ISurface {
public:
  Triangle(int _offset,  TriMesh* _mesh) : offset(_offset), mesh(_mesh) {};
  Intersection intersect(const Ray& ray);
  BBox get_bbox();
  vec3<int> get_indices() { return vec3<int>(mesh->indices[offset], mesh->indices[offset + 1], mesh->indices[offset + 2]); }
private:
  int offset;
  TriMesh *mesh;
};

#endif
