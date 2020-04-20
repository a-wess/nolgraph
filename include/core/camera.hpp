#ifndef _RAYS_CAMERA_
#define _RAYS_CAMERA_

#include <math/vec3.hpp>
#include <primitives/types.hpp>

class Camera {
 public:
  Camera(const vec3<float>& _origin, const vec3<float>& _dir, float _aspect_ratio);
  Ray shoot_ray(float u, float v);
  void update_axis();
  void update_origin(const vec3<float>& _origin) { origin = _origin; update_axis(); };
  void update_dir(const vec3<float>& _dir) { dir = _dir; update_axis(); };
  // private:
  vec3<float> origin;
  vec3<float> dir;
  vec3<float> right;
  vec3<float> up;
  float aspect_ratio;
};

#endif