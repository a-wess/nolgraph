#include <core/scene.hpp>

Intersection Scene::intersect (const Ray& ray) {
  Intersection result;
  result.position = {
    INFINITY,
    INFINITY,
    INFINITY
  };

  for (std::size_t i = 0; i < shapes.size(); i++) {
    auto intersection = shapes[i]->intersect(ray);
    if ((intersection.position - ray.origin).value() < (result.position - ray.origin).value()) {
      result.position = intersection.position;
      result.surface_normal = intersection.surface_normal;
    }
  }

  return result;
}
