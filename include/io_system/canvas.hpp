#ifndef _RAYS_CANVAS_
#define _RAYS_CANVAS_

#include <iostream>
#include <vector>
#include <cstdint>

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Canvas {
public:
  Canvas(int _width, int _height): buffer(_width * _height), width(_width), height(_height){};
  void set_pixel(unsigned int x, unsigned int y, const Pixel& pixel);
  std::vector<Pixel> buffer;
  unsigned int width;
  unsigned int height;
};

#endif