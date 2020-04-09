#include "canvas.hpp"

void Canvas::set_pixel(unsigned int x, unsigned int y, const Pixel &pixel) {
  buffer[y * width + x] = pixel;
}
