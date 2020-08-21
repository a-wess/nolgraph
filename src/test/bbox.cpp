#include <acc_structs/bbox.hpp>

#include "test.hpp"

bool can_init_to_infinitie() {
  BBox test;
  return test.mn.x == INFINITY && test.mn.y == INFINITY &&
         test.mn.z == INFINITY && test.mx.x == -INFINITY &&
         test.mx.x == -INFINITY && test.mx.z == -INFINITY;
}

bool extend_to_box() {
  BBox box({0.0, 0.0, 0.0}, {1.0, 1.0, 1.0});
  BBox box2({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f});

  box.expand(box2);

  return box.mn == vec3<float>(-1.0f, -1.0f, 0.0f) &&
         box.mx == vec3<float>(1.0f, 1.0f, 1.0f);
}

bool expand_to_point() {
  BBox box({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  vec3<float> p1 = {2.0f, 2.0f, 2.0f};
  box.expand(p1);
  bool test_1 = box.mx == p1;
  box.expand({1.0f, 1.0f, 1.0f});
  bool test_2 = box.mx == p1;
  return test_1 && test_2;
}

void Tests::test_bbox() {
  std::cout << "TEST BBOX\n";
  print_test("Init to infinite", can_init_to_infinitie());
  print_test("Expand to box", extend_to_box());
  print_test("Expend to point", expand_to_point());
}
