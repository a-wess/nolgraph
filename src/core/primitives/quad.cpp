#include "quad.hpp"

Intersection Quad::intersect(const Ray &ray) {
  Intersection result;

  auto indices = get_indices();
  vec3<float> p0 = mesh->vertices[indices[0]].position;
  vec3<float> p1 = mesh->vertices[indices[1]].position;
  vec3<float> p2 = mesh->vertices[indices[2]].position;
  vec3<float> p3 = mesh->vertices[indices[3]].position;

  auto normal = mesh->vertices[indices[0]].normal;
  float t = -normal.dot(ray.origin - p0) / normal.dot(ray.dir);
  if (t > 0) {
    auto e1 = p3 - p0;
    auto e2 = p1 - p0;
    auto p = ray.point_at(t) - p0;
    float pr1 = p.dot(e1) / e1.value();
    float pr2 = p.dot(e2) / e2.value();
    if ((pr1 < e1.value() && pr1 > 0) && (pr2 < e2.value() && pr2 > 0)) {
      result.hit = true;
      result.surface_normal = normal;
      result.position = ray.point_at(t);
      result.distance = (ray.dir * t).value();
      result.material = material;
    }
  }
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
