#ifndef _RAYS_SCENE_
#define _RAYS_SCENE_
#include <memory>
#include <vector>
#include "camera.hpp"
#include "material.h"
#include <primitives/types.hpp>
#include <primitives/triangle.hpp>
#include <math/vec3.hpp>
#include <acc_structs/bvh.hpp>

class Scene {
public:
  Intersection intersect(const Ray& ray);
  void prepare_scene();
  
  void add_mesh(TriMesh *mesh);
  void add_material(Cheap_material&& m) { materials.push_back(m); }

  Triangle& get_triangle(int index) { return triangles[index]; };
  const Cheap_material& get_material(int index) { return materials[index]; };
  Camera &get_camera() { return *camera; };
  void set_camera(Camera *cam) { camera = cam; };
  
  vec3<float> sun_direction;
private:
  std::vector<Cheap_material> materials;
  std::vector<Triangle> triangles;
  std::vector<TriMesh*> meshes;
  Camera* camera;
  BVH bvh;
};

#endif
