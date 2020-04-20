#ifndef _RAYS_TRIANGLE_
#define _RAYS_TRIANGLE_

#include "types.hpp"
#include <vector>
#include <memory>

const float EPSILON = 1e-7;
class TriangleMesh  {
public:
  TriangleMesh();
  std::vector<vec3<float>> positions;
  std::vector<vec3<float>> normals;
  std::vector<int> indices;
  int triangles_count;
};

class Triangle : public I_surface {
public:
  Triangle(int _indice,  TriangleMesh* _mesh) : indice(_indice), mesh(_mesh) {};
  float intersect(const Ray& ray);
  vec3<float> normal_at(const vec3<float>& point);
  int get_material_idx() { return 0; }
private:
  int indice;
  std::shared_ptr<TriangleMesh> mesh;
};

#endif
