#include <io_system/canvas.hpp>
#include <io_system/exporters.hpp>
#include <io_system/gltf.hpp>
#include <math/vec3.hpp>
#include <core/camera.hpp>
#include <core/renderer.hpp>
#include <primitives/types.hpp>
#include <primitives/sphere.hpp>
#include <primitives/triangle.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <thread>

const int IMAGE_WIDTH = 640;
const int IMAGE_HEIGHT = 360;

uint8_t to_255(float f) { return static_cast<uint8_t>(std::floor(f) > 255.0f ? 255.0f : std::floor(f)); }

void renderer() {
  Canvas image(IMAGE_WIDTH, IMAGE_HEIGHT);

  vec3<float> cam_origin({60.0f, -60.0f, 60.0f});
  vec3<float> cam_target({0.0f, 0.0f, 50.0f}); 
  Camera cam(cam_origin, (cam_target - cam_origin).norm(), static_cast<float>(IMAGE_WIDTH)/IMAGE_HEIGHT);

  vec3<float> sun(0.3f, -1.0f, 0.8f);

  Scene scene;
  scene.set_camera(&cam);
  scene.sun_direction = sun;

  TriangleMesh robot_mesh;

  scene.add_material({{0.0f, 0.0f, 1.0f}, 0.2f, 0.8f});

  for (int i = 0; i < robot_mesh.triangles_count; i++) {
    auto triangle = std::make_shared<Triangle>(i, &robot_mesh);
    scene.add_shape(triangle);
  }

  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);
  renderer.set_scene(&scene);
  renderer.render();
  // export_tga(image.buffer, {image.width, image.height});
  auto& samples = renderer.get_samples();
  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      auto& sample = samples[i * renderer.get_width() + j];
      image.set_pixel(j, i, {to_255(sample.x * 255), to_255(sample.y * 255), to_255(sample.z * 255)});
    }
  }

  export_tga(image.buffer, { image.width, image.height });
}

int main() {
  renderer();
  return 0;
}
