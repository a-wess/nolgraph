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

uint8_t to_255(float f) { return static_cast<uint8_t>(std::floor(f) > 255.0f ? 255.0f : std::floor(f)); }

void renderer() {
  Canvas image(1280, 720);
  vec3<float> cam_origin({60.0f, -60.0f, 60.0f});
  vec3<float> cam_target({0.0f, 0.0f, 50.0f}); 
  Camera cam(cam_origin, (cam_target - cam_origin).norm(), 16.0f/9.0f);
  vec3<float> sun(0.3f, -1.0f, 0.8f);
  Scene scene(sun.norm());

  TriangleMesh robot_mesh;
  scene.add_material({{0.0f, 0.0f, 1.0f}, 0.2f, 0.8f});
  //scene.add_material({{1.0f, 0.0f, 0.0f}, 0.0f, 1.0f});
  //scene.add_shape(std::make_shared<Sphere>(vec3<float>(-1.41f, 1.41f, 0.0f), 2.0f, 1));
  //scene.add_shape(std::make_shared<Sphere>(vec3<float>(1.41f, -1.41f, 0.0f), 2.0f, 0));
  for (int i = 0; i < robot_mesh.triangles_count; i++) {
    auto triangle = std::make_shared<Triangle>(i, &robot_mesh);
    scene.add_shape(triangle);
   }

  float total = image.width * image.height;

  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      float u = static_cast<float>(i)/image.width;
      float v = 1.0f - static_cast<float>(j)/image.height; // adjust z
      Ray view_ray = cam.shoot_ray(u, v);
      auto color = trace(view_ray, scene, 0);
      image.set_pixel(i, j, {to_255(255 * color.x), to_255(255 * color.y), to_255(255 * color.z)});
      //std::cout << "Set pixel " << i << ' ' << j << '\n';
      int progress = std::round((i * image.height + j) / total * 1000);
      
      if (progress % 10 == 0) std::cout << '\r' << progress / 10 << '%';
    }
  }

  export_tga(image.buffer, {image.width, image.height});
}

int main() {
  renderer();
  return 0;
}
