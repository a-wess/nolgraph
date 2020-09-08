#include "scene.hpp"
#include <cassert>

Intersection Scene::intersect(const Ray &ray) {
  Intersection res;
  for (auto& surface : surfaces) {
    auto i = surface->intersect(ray);
    if (i.hit && i.distance < res.distance) {
      res = i;
    }
  }
  return res;
}
