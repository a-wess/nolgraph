#include "exporters.hpp"
#include <fstream>
#include <stdint.h>
#include <arpa/inet.h>
#include <string_view>
#include <cstddef>

void export_png(const std::vector<std::byte>& buffer, const std::pair<int, int> size) {
  std::ofstream out{"test.png"};
}
