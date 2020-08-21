#ifndef _RAYS_MESH_
#define _RAYS_MESH_
#include <math/vec3.hpp>
#include <vector>

enum class MeshType { triangle, quad };

struct Vertex {
  vec3<float> position;
  vec3<float> normal;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<int> indices;
  int count = 0;
  MeshType type = MeshType::triangle;
  std::string name;
};

#endif