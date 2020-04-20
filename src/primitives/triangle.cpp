#include <primitives/triangle.hpp>

#ifndef _INCLUDE_ROBOT_
#define _INCLUDE_ROBOT_
#include <core/robot.hpp>
#endif

TriangleMesh::TriangleMesh() {
  for (int i = 0; i < NUM_ROBOT_OBJECT_VERTEX * 3; i += 3) {
    positions.push_back({
			 robotObject.vertices[i],
			 robotObject.vertices[i + 1],
			 robotObject.vertices[i + 2]
      });
    normals.push_back({
		       robotObject.normals[i],
		       robotObject.normals[i + 1],
		       robotObject.normals[i + 2]
      });
  }
  for (int i = 0; i < NUM_ROBOT_OBJECT_INDEX; i++) indices.push_back(robotObject.indices[i]);
  triangles_count = NUM_ROBOT_OBJECT_INDEX / 3;
}

float Triangle::intersect(const Ray& ray) {
  int i = indice  * 3;
  vec3<float> p0 = mesh->positions[mesh->indices[i]];
  vec3<float> p1 = mesh->positions[mesh->indices[i + 1]];
  vec3<float> p2 = mesh->positions[mesh->indices[i + 2]];
  vec3<float> e1 = p1 - p0;
  vec3<float> e2 = p2 - p0;
  float a, f, u, v;
  vec3<float> h = ray.dir.cross(e2);
  a = e1.dot(h);
  if (a > -EPSILON && a < EPSILON) return INFINITY;

  f = 1.0/a;
  vec3<float> s = ray.origin - p0;
  u = f * s.dot(h);
  if (u < 0.0 || u > 1.0) return INFINITY;

  vec3<float> q = s.cross(e1);
  v = f * ray.dir.dot(q);
  if (v < 0.0f || u + v > 1.0) return INFINITY;

  float t = f * e2.dot(q);
  if (t > EPSILON) return t;
  else return INFINITY;
}

vec3<float> Triangle::normal_at(const vec3<float>& point) {
  int i = indice * 3;
  vec3<float> p0 = mesh->positions[mesh->indices[i]];
  vec3<float> p1 = mesh->positions[mesh->indices[i + 1]];
  vec3<float> p2 = mesh->positions[mesh->indices[i + 2]];
  vec3<float> e1 = p1 - p0;
  vec3<float> e2 = p2 - p0;
  return e1.cross(e2).norm();
}
