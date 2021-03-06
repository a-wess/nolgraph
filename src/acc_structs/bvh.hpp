#ifndef _RAYS_BVH_
#define _RAYS_BVH_
#include <core/types.hpp>
#include <vector>

#include "primitive.hpp"

class BVH : public ISurface {
public:
  struct BVHNode {
    BBox box;
    int prim_offset;
    int prim_count;
    BVHNode *left;
    BVHNode *right;
  };
  Intersection intersect(const Ray &ray);
  Intersection debug(const Ray &ray);
  BVHNode *recursive_build(int start, int end);
  void push_primitive(Primitive *t) { primitives.push_back(PrimitiveInfo(t)); };
  void build();
  bool is_ready() { return primitives.size() > 0; };
  ~BVH();

private:
  Intersection rec_debug(BVHNode *node, const Ray &ray, int depth, int i);
  std::vector<PrimitiveInfo> primitives;
  std::vector<Primitive*> ordered_primitives;
  BVHNode *root;
};

#endif
