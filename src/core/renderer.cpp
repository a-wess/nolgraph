#include <core/renderer.hpp>
#include <thread>
#include <iostream>
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

void Renderer::process_tile(Tile &tile) { 
  int x = tile.x * tile_size;
  int y = tile.y * tile_size;
  for (int i = 0; i < tile_size; i++) {
    for (int j = 0; j < tile_size; j++) {
      float u = static_cast<float>(j + x) / horiz;
      float v = static_cast<float>(i + y) / vert;
      Ray from_eye = scene->get_camera().shoot_ray(u, 1.0f - v);
      auto color = integrator->render(*scene, from_eye);
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
