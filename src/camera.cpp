#include <camera.hpp>

Camera::Camera(const vec3<float>& _origin, const vec3<float>& _dir, float _aspect_ratio) :
  origin(_origin),
  dir(_dir),
  aspect_ratio(_aspect_ratio)
{
  update_axis();
}

void Camera::update_axis() {
  right = dir.cross(vec3<float>(0.0f, 0.0f, 1.0f));
  up = right.cross(right);
}
