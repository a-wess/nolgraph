#include <arpa/inet.h>
#include <stdint.h>

#include <cstddef>
#include <fstream>
#include <string_view>

#include "exporters.hpp"

void export_png(const std::vector<std::byte> &buffer,
                const std::pair<int, int> size) {
  std::ofstream out{"test.png"};
}
