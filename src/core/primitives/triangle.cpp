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
    auto v0 = p1 - p0, v1 = p2 - p0, v2 = result.position - p0;
    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    result.surface_normal = u * mesh->vertices[indices[0]].normal + v * mesh->vertices[indices[1]].normal + w * mesh->vertices[indices[2]].normal;
    result.hit = true;
    result.distance = (result.position - ray.origin).value();
    result.material = material;
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
