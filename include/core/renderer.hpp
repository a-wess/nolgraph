#ifndef _RAYS_RENDERER_
#define _RAYS_RENDERER_

#include <math/vec3.hpp>
#include <primitives/types.hpp>
#include <memory>
#include <vector>
#include "scene.hpp"

struct Tile {
  int x;
  int y;
  int w;
  int h;
};

class Renderer {
public:
  Renderer(int w, int h, int t_size = 32): tile_size(t_size) { set_resolution(w, h); };
  void render();
  void process_tile(Tile& tile);

  vec3<float> trace(const Ray& primary_ray, int depth);

  void set_scene(Scene *s) { scene = s; };
  void set_resolution(int x, int y);

  std::vector<vec3<float>> &get_samples() { return samples; };
  int get_width() { return horiz; };
  int get_height() { return vert; };

private:
  int vert;
  int horiz;
  int tile_size;
  Scene* scene;
  std::vector<vec3<float>> samples;
};

#endif
