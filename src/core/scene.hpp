#ifndef _RAYS_SCENE_
#define _RAYS_SCENE_

#include <acc_structs/bvh.hpp>
#include <math/vec3.hpp>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "material.hpp"
#include "triangle.hpp"
#include "types.hpp"

class Scene {
public:
  Intersection intersect(const Ray &ray);
  void prepare_scene() { bvh.build(); };
  void add_mesh(Mesh *mesh);
  void add_material(Cheap_material &&m) { materials.push_back(m); };
  Triangle &get_triangle(int index) { return *faces[index]; };
  const Cheap_material &get_material(int index) { return materials[index]; };
  Camera &get_camera() { return *camera; };
  void set_camera(Camera *cam) { camera = cam; };
  vec3<float> sun_direction;

private:
  std::vector<Cheap_material> materials;
  std::vector<Triangle *> faces;
  std::vector<Mesh *> meshes;
  BVH bvh;
  Camera *camera;
};

#endif
