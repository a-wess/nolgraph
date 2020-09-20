#include <core/camera.hpp>
#include <iostream>

Camera::Camera(const vec3<float> &_origin, const vec3<float> &_dir,
               float _aspect_ratio)
    : origin(_origin), dir(_dir), aspect_ratio(_aspect_ratio) {
  update_axis();
}

void Camera::update_axis() {
  dir = dir.norm();
  right = vec3<float>(0.0f, 0.0f, 1.0f).cross(dir).norm();
  up = dir.cross(right);
}

Ray Camera::shoot_ray(float u, float v) {
  Ray out;
  float x = 1.0f;
  float y = -2 * aspect_ratio * (u - 0.5);
  float z = 2 * (v - 0.5);

  out.dir.x = dir.x * x + right.x * y + up.x * z;
  out.dir.y = dir.y * x + right.y * y + up.y * z;
  out.dir.z = dir.z * x + right.z * y + up.z * z;

  out.dir = out.dir.norm();
  out.origin = origin;

  return out;
}
