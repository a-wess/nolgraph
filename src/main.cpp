#include <canvas.hpp>
#include <vector>
#include <exporters.hpp>
#include <iostream>
#include <math.hpp>

bool circle(int x, int y, int r) {
  return r*r - x*x - y*y > 0;
}

int main() {
  Canvas image(320, 240);
  vec3<float> camera_origin(5, 5, 5);
  vec3<float> camera_dir(-5, -5, -5);

  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      image.set_pixel(i, j, {255, 0, 0});
      if (circle(i - image.width/2,j - image.height/2, 120)) image.set_pixel(i, j, {0, 0, 255});
    }
  }

  export_tga(image.buffer, {image.width, image.height});
  return 0;
}
