#pragma once
#include "math/math.hpp"
#include "objects.hpp"
#include <memory>
#include <vector>

struct PBR_material {
  vec3<float> base_color;
  float metaleness;
  float roughness;
};

struct Cheap_material {
  vec3<float> diffuse;
  float specular_coef;
  float diffuse_coef;
};

class Scene {
public:
  Scene(vec3<float> s): sun(s) {};
  std::pair<int, float> intersect(const Ray& ray) const;

  I_surface& get_shape(int index) const { return *(shapes[index]); };
  void add_shape(std::shared_ptr<I_surface>&& shape_ptr) { shapes.push_back(shape_ptr); };

  const Cheap_material& get_material(int index) const { return materials[index]; };
  void add_material(Cheap_material&& m) { materials.push_back(m); }

  vec3<float> sun;
private:
  std::vector<Cheap_material> materials;
  std::vector<std::shared_ptr<I_surface>> shapes;
};

vec3<float> trace(const Ray& primary_ray, const Scene& scene, int depth);
vec3<float> shade_point(const Ray& primary_ray, const Scene& scene);
