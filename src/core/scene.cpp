#include <core/scene.hpp>
#include <cassert>

Intersection Scene::intersect (const Ray& ray) {
  assert(bvh.is_ready());
  return bvh.traverse(ray);
}

void Scene::add_mesh(TriMesh* mesh) {
  meshes.push_back(mesh);
  for(int i = 0; i < mesh->triangles_count; i++) {
    triangles.push_back(Triangle(i * 3, mesh));
  }
}

void Scene::prepare_scene() {
  assert(!bvh.is_ready());
  for (auto& t : triangles)
    bvh.push_primitive(&t);
  bvh.build();
}
