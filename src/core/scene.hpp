#ifndef _RAYS_SCENE_
#define _RAYS_SCENE_

#include <acc_structs/bvh.hpp>
#include <acc_structs/primitive.hpp>
#include <math/vec3.hpp>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "material.hpp"
#include "types.hpp"
#include "mesh.hpp"

class Scene {
public:
  Intersection intersect(const Ray &ray);
  void add_surface(ISurface *surface) { surfaces.push_back(surface); };
  Camera &get_camera() { return *camera; };
  void set_camera(Camera *cam) { camera = cam; };
  vec3<float> sun_direction;
private:
  std::vector<ISurface*> surfaces;
  Camera *camera;
};

#endif
