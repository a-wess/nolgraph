#include <core/renderer.hpp>
#include <thread>

void render_kernel(Renderer* renderer, Tile* tiles, int start, int n) {
  for (auto i = start; i < start + n; i++)
    renderer->process_tile(tiles[i]);
  std::cout << "Thread has finished " << start << '\n';
}

void Renderer::render() {
  std::vector<Tile> tiles;
  int rows = get_width() / 32;
  int cols = get_height() / 32;
  std::vector<std::thread> render_workers;
  
  for (int i = 0; i < rows * cols; i++) {
    Tile t;
    t.x = i % rows;
    t.y = i / rows;
    tiles.push_back(t);
  }

  int tile_count = rows * cols;
  int tiles_per_thread = std::ceil(tile_count / 8.0f);
  std::cout << tile_count << ' ' << tiles_per_thread << '\n';

  for (int i = 0; i < tile_count; i += tiles_per_thread) {
    std::thread tmp(render_kernel, this, tiles.data(), i, i + tiles_per_thread < tile_count ? tiles_per_thread : tile_count - i);
    std::cout << i << ' ' << ((i + tiles_per_thread) < tile_count ? tiles_per_thread : tile_count - i) << '\n';
    render_workers.push_back(std::move(tmp));
  }

  for (auto& worker : render_workers)
    worker.join();
  std::cout << "Threads are finished\n";
}

// TODO: Solve self collision problem
vec3<float> Renderer::trace(const Ray& primary_ray, int depth) {
  vec3<float> color(0.0f, 0.0f, 0.0f);
  if (depth > 1) return vec3<float>(0.8f,0.2f,0.0f);

  auto intersection = scene->intersect(primary_ray);
  if (intersection.position.x != INFINITY
      && intersection.position.y != INFINITY
      && intersection.position.z != INFINITY) {
    auto& material = scene->get_material(0);
    auto p = intersection.position;
    auto N = intersection.surface_normal;

    color += material.diffuse_coef * std::max(N.dot(scene->sun_direction), 0.0f) * material.diffuse;
  
    // Specular part calculation
    if (material.specular_coef > 0.05) {
      auto view_vector = primary_ray.dir * -1.0f;
      auto light_vector = N * 2 * view_vector.dot(N) - view_vector;
      
      Ray from_specular;
      from_specular.origin = p + N * 1e-4;
      from_specular.dir = light_vector;
      float specular = pow(std::max(light_vector.dot(N), 0.0f), 1);
      auto specular_color = trace(from_specular, depth + 1);
      specular_color *= material.specular_coef * specular;
      //    if (specular_color.value() > 0)
      color += specular_color;//specular_color * material.specular_coef * specular;
    }
    return color;
  } else {
    return vec3<float>(0.8f,0.2f,0.0f);
  }
};


void Renderer::process_tile(Tile& tile) {
  int x = tile.x * tile_size;
  int y = tile.y * tile_size;
  for(int i = 0; i < tile_size; i++) {
    for(int j = 0; j < tile_size; j++) {
      float u  = static_cast<float>(j + x) / horiz;
      float v = static_cast<float>(i + y) / vert;
      Ray from_eye = scene->get_camera().shoot_ray(u, 1.0f - v);
      auto color = trace(from_eye, 0);
      // samples[i * tile.w + j] = color;
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
