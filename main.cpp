#include "io_utils/canvas.hpp"
#include "io_utils/exporters.hpp"
#include "math/math.hpp"
#include "core/camera.hpp"
#include "core/objects.hpp"
#include "core/renderer.hpp"
#include <vector>
#include <iostream>
#include <memory>

uint8_t to_255(float f) { return static_cast<uint8_t>(std::floor(f) > 255.0f ? 255.0f : std::floor(f)); }

int main() {
  Canvas image(640, 480);
  Camera cam({8.0f, 8.0f, 8.0f}, {-1.0f, -1.0f, -1.0f}, 4.0f/3.0f);
  vec3<float> sun(0.3f, 1.0f, 0.8f);
  Scene scene(sun.norm());
  scene.add_material({{0.0f, 0.0f, 1.0f}, 1.0f, 0.0f});
  scene.add_material({{1.0f, 0.0f, 0.0f}, 0.0f, 1.0f});
  scene.add_shape(std::make_shared<Sphere>(vec3<float>(-1.41f, 1.41f, 0.0f), 2.0f, 1));
  scene.add_shape(std::make_shared<Sphere>(vec3<float>(1.41f, -1.41f, 0.0f), 2.0f, 0));
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      float u = static_cast<float>(i)/image.width;
      float v = 1.0f - static_cast<float>(j)/image.height; // adjust z
      Ray view_ray = cam.shoot_ray(u, v);
      auto color = trace(view_ray, scene, 0);
      image.set_pixel(i, j, {to_255(255 * color.x), to_255(255 * color.y), to_255(255 * color.z)});
    }
  }

  export_tga(image.buffer, {image.width, image.height});
  return 0;
}
