#include <core/camera.hpp>
#include <core/scene.hpp>
#include <math/vec3.hpp>

Scene get_scene_robot() {
  vec3<float> cam_origin({100.0f, -100.0f, 20.0f});
  vec3<float> cam_target({0.0f, 0.0f, 0.0f});
  vec3<float> sun(0.3f, -1.0f, 0.8f);

  Scene scene;
  scene.set_camera(new Camera(cam_origin, (cam_target - cam_origin).norm(),
                              static_cast<float>(16.0f) / 9.0f));
  scene.sun_direction = sun;

  scene.add_material({{0.0f, 0.0f, 1.0f}, 0.2f, 0.8f});

  return scene;
}
