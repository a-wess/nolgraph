#include <acc_structs/bbox.hpp>
#include <cmath>

void BBox::expand(const BBox &box) {
  mn = {std::min(mn.x, box.mn.x), std::min(mn.y, box.mn.y),
        std::min(mn.z, box.mn.z)};
  mx = {std::max(mx.x, box.mx.x), std::max(mx.y, box.mx.y),
        std::max(mx.z, box.mx.z)};
}

void BBox::expand(const vec3<float> &point) {
  mn = {std::min(mn.x, point.x), std::min(mn.y, point.y),
        std::min(mn.z, point.z)};
  mx = {std::max(mx.x, point.x), std::max(mx.y, point.y),
        std::max(mx.z, point.z)};
}

float BBox::area() {
  // case of empty box
  if (mx.x == -INFINITY || mn.x == INFINITY)
    return 0.0f;
  auto d = mx - mn;
  return 2 * (fabs(d.x * d.z) + fabs(d.x * d.y) + fabs(d.z * d.y));
}

Intersection BBox::intersect(const Ray &ray) {
  Intersection res;
  float tmin = (mn.x - ray.origin.x) / ray.dir.x;
  float tmax = (mx.x - ray.origin.x) / ray.dir.x;

  if (tmin > tmax)
    std::swap(tmin, tmax);

  float tymin = (mn.y - ray.origin.y) / ray.dir.y;
  float tymax = (mx.y - ray.origin.y) / ray.dir.y;

  if (tymin > tymax)
    std::swap(tymin, tymax);

  if ((tmin > tymax) || (tymin > tmax))
    return res;

  if (tymin > tmin)
    tmin = tymin;

  if (tymax < tmax)
    tmax = tymax;

  float tzmin = (mn.z - ray.origin.z) / ray.dir.z;
  float tzmax = (mx.z - ray.origin.z) / ray.dir.z;

  if (tzmin > tzmax)
    std::swap(tzmin, tzmax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return res;

  if (tzmin > tmin)
    tmin = tzmin;

  if (tzmax < tmax)
    tmax = tzmax;
  res.hit = true;
  res.distance = (ray.point_at(tmin) - ray.origin).value();
  return res;
}

Intersection BBox::debug(const Ray &r) {
  Intersection res;
  res.hit = false;

  float tmin = -INFINITY;
  float tmax = INFINITY;

  for (int i = 0; i < 3; i++) {
    float t1 = (mn[i] - r.origin[i]) / r.dir[i];
    float t2 = (mx[i] - r.origin[i]) / r.dir[i];
    if (t1 > t2)
      std::swap(t1, t2);
    if ((tmin > t2) || (t1 > tmax)) {
      return res;
    }
    if (t1 > tmin)
      tmin = t1;
    if (t2 < tmax)
      tmax = t2;
  }
  res.hit = true;
  res.position = r.point_at(tmin);
  res.distance = (res.position - r.origin).value();

  auto size = mx - mn;
  auto center = mn + size / 2;
  auto localPoint = res.position - center;
  float min = std::numeric_limits<float>::max();
  float distance = std::abs(size.x - std::abs(localPoint.x));
  if (distance < min) {
    min = distance;
    res.surface_normal = {1, 0, 0};
    res.surface_normal *= (localPoint.x > 0) ? 1 : -1;
  }
  distance = std::abs(size.y - std::abs(localPoint.y));
  if (distance < min) {
    min = distance;
    res.surface_normal = {0, 1, 0};
    res.surface_normal *= (localPoint.y > 0) ? 1 : -1;
  }
  distance = std::abs(size.z - std::abs(localPoint.z));
  if (distance < min) {
    min = distance;
    res.surface_normal = {0, 0, 1};
    res.surface_normal *= (localPoint.z > 0) ? 1 : -1;
  }

  return res;
}

int BBox::maximum_extent() {
  auto diagonal = mx - mn;
  if (diagonal.x > diagonal.y && diagonal.x > diagonal.z)
    return 0;
  if (diagonal.y > diagonal.z && diagonal.y >= diagonal.x)
    return 1;
  if (diagonal.z >= diagonal.x && diagonal.z >= diagonal.y)
    return 2;
  return -1;
}
