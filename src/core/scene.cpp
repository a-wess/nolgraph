#include "scene.hpp"

#include <acc_structs/bvh.hpp>
#include <cassert>
#include <iostream>

Intersection Scene::intersect(const Ray &ray) {
  assert(bvh.is_ready());
  Intersection res;
  // for (auto& s : faces) {
  auto i = bvh.intersect(ray);
  if (i.hit && i.distance < res.distance)
    res = i;
  // }
  return res;
}

void Scene::add_mesh(Mesh *mesh) {
  meshes.push_back(mesh);
  for (int i = 0; i < mesh->count; i++) {
    if (mesh->type == MeshType::triangle) {
      faces.push_back(new Triangle(i * 3, mesh));
      bvh.push_primitive(faces.back());
      // std::cout << mesh->count << ' ' << mesh->indices.size()
      // << " " << mesh->name << '\n';
    }
  }
}
