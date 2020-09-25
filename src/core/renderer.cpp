#include <core/renderer.hpp>
#include <thread>
#include <iostream>
#include <math/helpers.hpp>
#include <queue>
#include <mutex>
#include <random>

std::mutex tile_queue_lock;

void render_kernel(Renderer *renderer, std::queue<Tile>& tiles) {
  bool proccessing = true;
  while(proccessing) {
    tile_queue_lock.lock();
    if (!tiles.empty()) {
      auto tile = tiles.front();
      tiles.pop();
      tile_queue_lock.unlock();
      renderer->process_tile(tile);
    } else {
      tile_queue_lock.unlock();
      break;
    }
  }
  // renderer->process_tile(tiles[i]);
  std::cout << "Thread has finished \n";
}

void Renderer::render() {
  std::queue<Tile> tiles;
  int rows = get_width() / 32;
  int cols = get_height() / 32;
  std::vector<std::thread> render_workers;

  for (int i = 0; i < rows * cols; i++) {
    Tile t;
    t.x = i % rows;
    t.y = i / rows;
    tiles.push(t);
  }

  for (int i = 0; i < 12; i++) {
    std::thread tmp(render_kernel, this, std::ref(tiles));
    render_workers.push_back(std::move(tmp));
  }

  for (auto &worker : render_workers)
    worker.join();
  std::cout << "Threads are finished\n";
}

vec3<float> Renderer::trace_path(const Ray &primary_ray, int depth) {
  if (depth == 0) return {0.0f, 0.0f, 0.0f};

  auto intersection = scene->intersect(primary_ray);
  if (intersection.position.x != std::numeric_limits<float>::infinity() &&
      intersection.position.y != std::numeric_limits<float>::infinity() &&
      intersection.position.z != std::numeric_limits<float>::infinity()) {
    auto &material = *intersection.material;
    auto p = intersection.position;
    auto N = intersection.surface_normal;

    Ray emited_ray;
    emited_ray.origin = intersection.position + vec_in_direction(N, 5.0f * std::numeric_limits<float>::epsilon());
    emited_ray.dir = sample_hemishpere(N);

    float pdf = 1.0f / (2.0f * M_PI);
    auto spectral_radiance = trace_path(emited_ray, depth - 1);
    auto radiance = (material.diffuse / static_cast<float>(M_PI)) * N.dot(emited_ray.dir) * spectral_radiance / pdf;
    return radiance;
  } else {
    auto t = 0.5f * primary_ray.dir.norm().y + 1.0f;
    return (1.0f-t) * vec3<float>(1.0, 1.0, 1.0) + t * vec3<float>(0.5, 0.7, 1.0);
  }
};

void Renderer::process_tile(Tile &tile) { 
  int x = tile.x * tile_size;
  int y = tile.y * tile_size;
  float scale = 1.0f / rays_per_sample;
  for (int i = 0; i < tile_size; i++) {
    for (int j = 0; j < tile_size; j++) {
      auto color = vec3<float>(0.0f, 0.0f, 0.0f);
      float u = static_cast<float>(j + x) / horiz;
      float v = static_cast<float>(i + y) / vert;
      for (int k = 0; k < rays_per_sample; k++) {
        Ray from_eye = scene->get_camera().shoot_ray(u, 1.0f - v);
        vec3<float> radiance = trace_path(from_eye, 8);
        color += radiance;
      }
      color /= static_cast<float>(rays_per_sample);
      samples[(y + i) * horiz + x + j] = color;
    }
  }
}

void Renderer::set_resolution(int x, int y) {
  horiz = x;
  vert = y;
  padding_h = x % tile_size ? tile_size - x % tile_size : 0;
  padding_v = y % tile_size ? tile_size - y % tile_size : 0;
  std::cout << get_width() << ' ' << get_height() << '\n';
  samples.resize(get_width() * get_height());
}
