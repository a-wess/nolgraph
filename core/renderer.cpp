#include "renderer.hpp"

std::pair<int, float> Scene::intersect (const Ray& ray) const {
  auto intersection = std::make_pair(-1, INFINITY);
  for (std::size_t i = 0; i < shapes.size(); i++) {
    float d_to_shape = shapes[i]->intersect(ray);
    if (d_to_shape < intersection.second) {
      intersection.second = d_to_shape;
      intersection.first = i;
    }
  }

  return intersection;
}

// TODO: Solve self collision problem
vec3<float> trace(const Ray& primary_ray, const Scene& scene, int depth) {
  vec3<float> color(0.0f, 0.0f, 0.0f);
  if (depth > 1) return vec3<float>(0.8f,0.2f,0.0f);

  auto intersection = scene.intersect(primary_ray);
  if (intersection.first > -1) {
    auto& surface = scene.get_shape(intersection.first);
    auto& material = scene.get_material(surface.get_material_idx());
    auto p = primary_ray.point_at(intersection.second);
    auto N = surface.normal_at(p);

    color += material.diffuse_coef * std::max(N.dot(scene.sun), 0.0f) * material.diffuse;
  
    // Specular part calculation
    if (material.specular_coef > 0.05) {
      auto view_vector = primary_ray.dir * -1.0f;
      auto light_vector = N * 2 * view_vector.dot(N) - view_vector;
      if (depth > 0) std::cout << material.specular_coef << '\n';
      Ray from_specular;
      from_specular.origin = p + N * 1e-4;
      from_specular.dir = light_vector;
      float specular = pow(std::max(light_vector.dot(N), 0.0f), 1);
      auto specular_color = trace(from_specular, scene, depth + 1);
      specular_color *= material.specular_coef * specular;
      //    if (specular_color.value() > 0)
      color += specular_color;//specular_color * material.specular_coef * specular;
    }
    return color;
  } else {
    return vec3<float>(0.8f,0.2f,0.0f);
  }
};
