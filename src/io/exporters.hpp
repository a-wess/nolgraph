#ifndef _RAYS_EXPORTERS_
#define _RAYS_EXPORTERS_

#include <utility>
#include <vector>

#include "canvas.hpp"

void export_bmg(const std::vector<Pixel> &buffer);
void export_png(const std::vector<Pixel> &buffer,
                const std::pair<unsigned int, unsigned int> &size);
void export_tga(const std::vector<Pixel> &buffer,
                const std::pair<uint16_t, uint16_t> &size);

#endif