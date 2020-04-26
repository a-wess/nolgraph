#ifndef _RAYS_SCENE_
#define _RAYS_SCENE_
#include <memory>
#include <vector>
#include "camera.hpp"
#include "material.h"
#include <primitives/types.hpp>
#include <math/vec3.hpp>

class Scene {
public:
  Intersection intersect(const Ray& ray);

  I_surface& get_shape(int index) const { return *(shapes[index]); };
  void add_shape(std::shared_ptr<I_surface>&& shape_ptr) { shapes.push_back(shape_ptr); };
  void add_material(Cheap_material&& m) { materials.push_back(m); }

  const Cheap_material& get_material(int index) { return materials[index]; };
  Camera &get_camera() { return *camera; };
  void set_camera(Camera *cam) { camera = cam; };

  vec3<float> sun_direction;
private:
  std::vector<Cheap_material> materials;
  std::vector<std::shared_ptr<I_surface>> shapes;
  Camera* camera;
};

#endif
