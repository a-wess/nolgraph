#ifndef _RAYS_TEST_
#define _RAYS_TEST_
#include <iostream>
#include <string_view>

class Tests {
public:
  void test_bbox();
  void print_test(std::string_view message, bool result) {
    std::cout << message << ' ';
    std::cout << (result ? "PASS\n" : "FAIL\n");
  };
};

#endif
