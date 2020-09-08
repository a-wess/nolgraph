#include <core/camera.hpp>
#include <core/renderer.hpp>
#include <core/types.hpp>
#include <io/canvas.hpp>
#include <io/exporters.hpp>
#include <io/obj_loader.hpp>
#include <acc_structs/bvh.hpp>
#include <core/primitives/triangle.hpp>
#include <core/primitives/quad.hpp>
#include <iostream>
#include <math/vec3.hpp>
#include <memory>
#include <thread>
#include <vector>

Material specimen_material = {{0.0f, 1.0f, 0.0f}, 0.0, 1.0};

const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = 800;

uint8_t to_255(float f) {
  return static_cast<uint8_t>(std::floor(f) > 255.0f ? 255.0f : std::floor(f));
}

void renderer() {
  OBJ_Loader loader;
  loader.parse_file("cornell.obj");
  std::cout << "loaded Obj File\n";
  Canvas image(IMAGE_WIDTH, IMAGE_HEIGHT);
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

  BVH bvh;
  for (auto &mesh : loader.get_meshes()) {
    for (int i = 0; i < mesh.count; i++) {
      if (mesh.type == MeshType::triangle) bvh.push_primitive(new Triangle(i * 3, &mesh, &specimen_material));
      else if (mesh.type == MeshType::quad) bvh.push_primitive(new Quad(i * 4, &mesh, &specimen_material));
    }
  }
  bvh.build();

  Scene scene;
  scene.add_surface(&bvh);
  vec3<float> cam_origin = {-273, -500, 273};
  vec3<float> cam_target = {0, 0, 273};
  scene.sun_direction = {-0.3f, -1.0f, 0.8};
  scene.set_camera(new Camera(cam_origin, {0.0f, 1.0f, 0.0f},
                              static_cast<float>(1.0f) / 1.0f));
  renderer.set_scene(&scene);
  renderer.render();

  auto &samples = renderer.get_samples();
  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      auto &sample = samples[i * renderer.get_width() + j];
      image.set_pixel(j, i,
                      {to_255(sample.x * 255), to_255(sample.y * 255),
                       to_255(sample.z * 255)});
    }

    export_tga(image.buffer, {image.width, image.height});
  }
}

void test() {
  OBJ_Loader loader;
  loader.parse_file("cornell.obj");
  auto &meshes = loader.get_meshes();
  std::cout << "Meshes count: " << meshes.size() << '\n';
  std::cout << meshes.front().count << '\n';
}

int main() {
  // renderer();
  test();
  return 0;
}