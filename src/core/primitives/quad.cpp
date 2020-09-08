#include "quad.hpp"

Intersection Quad::intersect(const Ray &ray) {
  Intersection result;

  auto indices = get_indices();
  vec3<float> p0 = mesh->vertices[indices[0]].position;
  vec3<float> p1 = mesh->vertices[indices[1]].position;
  vec3<float> p2 = mesh->vertices[indices[2]].position;
  vec3<float> p3 = mesh->vertices[indices[3]].position;
  // TO DO WRIGHT INTERSECTION FUNCTION
  return result;
}

BBox Quad::get_bbox() {
  auto indices = get_indices();
  auto &p1 = mesh->vertices[indices[0]].position;
  auto &p2 = mesh->vertices[indices[1]].position;
  auto &p3 = mesh->vertices[indices[2]].position;
  auto &p4 = mesh->vertices[indices[3]].position;

  vec3<float> b_min = {std::min(p1.x, std::min(p2.x, std::min(p4.x, p3.x))),
                       std::min(p1.y, std::min(p2.y, std::min(p4.y, p3.y))),
                       std::min(p1.z, std::min(p2.z, std::min(p4.z, p3.z)))};
  vec3<float> b_max = {std::max(p1.x, std::max(p2.x, std::max(p4.x, p3.x))),
                       std::max(p1.y, std::max(p2.y, std::max(p4.y, p3.y))),
                       std::max(p1.z, std::max(p2.z, std::max(p4.z, p3.z)))};

  return BBox(b_min, b_max);
}
