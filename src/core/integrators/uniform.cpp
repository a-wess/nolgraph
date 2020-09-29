#include "uniform.hpp"
#include <random>

vec3<float> UniformRandomIntegrator::sample_hemishpere() {
    float r1 = dist(gen);
    float r2 = dist(gen);
    float z = r1;
    float x = sqrt(1.0f - r1*r1) * cos(2*M_PI * r2);
    float y = sqrt(1.0f - r1*r1) * sin(2*M_PI * r2);

    return vec3(x, y, z);
}

vec3<float> UniformRandomIntegrator::sample_hemishpere(const vec3<float>& direction) {
    vec3<float> u = std::abs(direction.x) > 0.9f ? vec3<float>(0.0f, 1.0f, 0.0f) : vec3<float>(1.0f, 0.0f, 0.0f);
    auto s = direction.cross(u).norm();
    auto t = s.cross(direction);
    auto sampled = sample_hemishpere();
    return sampled.x * s + sampled.y * t + sampled.z * direction;
}

vec3<float> UniformRandomIntegrator::render(const Scene& scene, const Ray& ray) {
    vec3<float> color(0.0f, 0.0f, 0.0f);
    for (int k = 0; k < samples; k++) {
        vec3<float> radiance = trace_path(scene, ray, 8);
        color += radiance;
    }
    color *= 2.0f * M_PI;
    color /= static_cast<float>(samples);
    return color;
}

vec3<float> UniformRandomIntegrator::trace_path(const Scene& scene, const Ray &primary_ray, int depth) {
  if (depth == 0) return {0.0f, 0.0f, 0.0f};

  auto intersection = scene.intersect(primary_ray);
  if (intersection.position.x != std::numeric_limits<float>::infinity() &&
      intersection.position.y != std::numeric_limits<float>::infinity() &&
      intersection.position.z != std::numeric_limits<float>::infinity()) {
    auto &material = *intersection.material;
    auto p = intersection.position;
    auto N = intersection.surface_normal;

    Ray emited_ray;
    emited_ray.origin = intersection.position + N * 5.0f * std::numeric_limits<float>::epsilon();
    emited_ray.dir = sample_hemishpere(N);

    float pdf = 1.0f / (2.0f * M_PI);
    auto spectral_radiance = trace_path(scene, emited_ray, depth - 1);
    auto radiance = (material.diffuse / static_cast<float>(M_PI)) * N.dot(emited_ray.dir) * spectral_radiance;
    return radiance;
  } else {
    auto t = 0.5f * primary_ray.dir.norm().y + 1.0f;
    return (1.0f-t) * vec3<float>(1.0, 1.0, 1.0) + t * vec3<float>(0.5, 0.7, 1.0);
  }
};