#include <core/camera.hpp>
#include <core/renderer.hpp>
#include <core/types.hpp>
#include <io/canvas.hpp>
#include <io/exporters.hpp>
#include <io/obj_loader.hpp>
#include <acc_structs/bvh.hpp>
#include <core/primitives/triangle.hpp>
#include <core/primitives/quad.hpp>
#include <core/primitives/sphere.hpp>
#include <core/primitives/plane.hpp>
#include <core/integrators/uniform.hpp>
#include <iostream>
#include <math/vec3.hpp>
#include <memory>
#include <thread>
#include <vector>

Material specimen_material = {
  {1.0f, 0.84f, 0.0f},
  {0.0f, 0.0f, 0.0f},
  0.0f,
  0.8f,
  0.2f
};

Material specimen_material_2 = {
  {0.4f, 0.1f, 0.5f},
  {0.4f, 0.4f, 0.1f},
  0.0f,
  0.8f,
  0.2f
};

const int IMAGE_WIDTH = 1280;
const int IMAGE_HEIGHT = 720;

float clamp (float x, float min, float max) { return x < min ? min : x > max ? max : x; }

uint8_t to_255(float f) {
  return static_cast<uint8_t>(std::floor(f) > 255.0f ? 255.0f : std::floor(f));
}

void renderer() {
  OBJ_Loader loader;
  loader.parse_file("llucy.obj");
  std::cout << "loaded Obj File\n";
  Canvas image(IMAGE_WIDTH, IMAGE_HEIGHT);
  Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT, new UniformRandomIntegrator(16));

  BVH bvh;
  for (auto &mesh : loader.get_meshes()) {
    std::cout << mesh.name << ' ' << mesh.count << '\n';
    for (int i = 0; i < mesh.count; i++) {
      if (mesh.type == MeshType::triangle) bvh.push_primitive(new Triangle(i * 3, &mesh, &specimen_material));
      else if (mesh.type == MeshType::quad) bvh.push_primitive(new Quad(i * 4, &mesh, &specimen_material));
    }
  }
  bvh.build();

  Scene scene;
  scene.add_surface(&bvh);
  scene.add_surface(new Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, &specimen_material_2));
  //scene.add_surface(new Sphere({0.0, 0.0, 2.0}, 2, &specimen_material));
  //scene.add_surface(new Sphere({600.0, 0.0, 0.0}, 100, &specimen_material));
  //scene.add_surface(new Sphere({0.0, 600.0, 0.0}, 100, &specimen_material));
  vec3<float> cam_origin = {0.0f, 4.0f, 2.0f};
  vec3<float> cam_target = {0.0f, 0.0f, 2.0f};
  scene.sun_direction = {0.0f, 1.0f, 1.0};
  scene.set_camera(new Camera(cam_origin, (cam_target - cam_origin).norm(),
                              static_cast<float>(16.0f) / 9.0f));
  renderer.set_scene(&scene);
  renderer.render();

  auto &samples = renderer.get_samples();
  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      auto &sample = samples[i * renderer.get_width() + j];
      image.set_pixel(j, i,
                      {to_255(clamp(sample.z, 0.0f, 0.99f) * 256.0f), to_255(clamp(sample.y, 0.0f, 0.99f) * 256.0f),
                       to_255(clamp(sample.x, 0.0f, 0.99f) * 256.0f)});
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
  renderer();
  return 0;
}