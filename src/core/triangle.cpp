#include "triangle.hpp"

Intersection Triangle::intersect(const Ray &ray) {
  Intersection result;

  auto indices = get_indices();
  vec3<float> p0 = mesh->vertices[indices[0]].position;
  vec3<float> p1 = mesh->vertices[indices[1]].position;
  vec3<float> p2 = mesh->vertices[indices[2]].position;
  vec3<float> e1 = p1 - p0;
  vec3<float> e2 = p2 - p0;
  float a, f, u, v;
  vec3<float> h = ray.dir.cross(e2);
  a = e1.dot(h);
  if (a > -EPSILON && a < EPSILON)
    return result;

  f = 1.0 / a;
  vec3<float> s = ray.origin - p0;
  u = f * s.dot(h);
  if (u < 0.0 || u > 1.0)
    return result;

  vec3<float> q = s.cross(e1);
  v = f * ray.dir.dot(q);
  if (v < 0.0f || u + v > 1.0)
    return result;

  float t = f * e2.dot(q);
  if (t > EPSILON) {
    result.position = ray.point_at(t);
    result.surface_normal = (p1 - p0).cross(p2 - p0).norm();
    result.hit = true;
    result.distance = (result.position - ray.origin).value();
  }
  return result;
}

BBox Triangle::get_bbox() {
  auto indices = get_indices();
  auto &p1 = mesh->vertices[indices[0]].position;
  auto &p2 = mesh->vertices[indices[1]].position;
  auto &p3 = mesh->vertices[indices[2]].position;

  vec3<float> b_min = {std::min(p1.x, std::min(p2.x, p3.x)),
                       std::min(p1.y, std::min(p2.y, p3.y)),
                       std::min(p1.z, std::min(p2.z, p3.z))};
  vec3<float> b_max = {std::max(p1.x, std::max(p2.x, p3.x)),
                       std::max(p1.y, std::max(p2.y, p3.y)),
                       std::max(p1.z, std::max(p2.z, p3.z))};

  return BBox(b_min, b_max);
}