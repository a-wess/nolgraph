#ifndef _RAYS_RENDERER_
#define _RAYS_RENDERER_

#include <core/types.hpp>
#include <math/vec3.hpp>
#include <memory>
#include <vector>

#include "scene.hpp"
#include "integrators/integrator.hpp"

struct Tile {
  int x;
  int y;
};

class Renderer {
public:
  Renderer(int w, int h, Integrator* integrator, int t_size = 32):
    integrator(integrator),
    tile_size(t_size)
  {
    set_resolution(w, h);
  };
  void render();
  void process_tile(Tile &tile);

  void set_scene(Scene *s) { scene = s; };
  void set_resolution(int x, int y);

  std::vector<vec3<float>> &get_samples() { return samples; };
  int get_width() { return horiz + padding_h; };
  int get_height() { return vert + padding_v; };

private:
  // Buffer related
  int vert;
  int horiz;
  int padding_h;
  int padding_v;
  int tile_size;
  // Renderer related
  Scene *scene;
  std::unique_ptr<Integrator> integrator;
  std::vector<vec3<float>> samples;
};

#endif
