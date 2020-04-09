#include "exporters.hpp"
#include <fstream>
#include <array>

void export_tga(const std::vector<Pixel>& buffer, const std::pair<uint16_t, uint16_t>& size) {
  std::ofstream out_img("canvas.tga", std::ios::binary);
  
  std::array<uint8_t, 12> header = {
    0, // id length
    0, // colormap type
    2, // image type
    0,0,0,0,0, // color map specifications
    0,0,0,0, // xy
  };
  uint8_t pixel_depth = 24;
  uint8_t image_descriptor = 0b100000;
  out_img.write((char *)header.data(), header.size());
  out_img.write((char *)&size.first, 2);
  out_img.write((char *)&size.second, 2);
  out_img.write((char *)&pixel_depth, 1);
  out_img.write((char *)&image_descriptor, 1);
  out_img.write((char *)buffer.data(), sizeof(Pixel) * size.first * size.second);
  out_img.close();
}
