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
  Intersection intersect(const Ray& ray);
private:
  int indice;
  TriangleMesh *mesh;
};

#endif
