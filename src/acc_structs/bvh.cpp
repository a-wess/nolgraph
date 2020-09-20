#include <acc_structs/bvh.hpp>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>

const int SAH_BUCKET_SIZE = 12;

struct SAHBucket {
  int count = 0;
  BBox box;
};

BVH::BVHNode *init_leaf(BBox &box, int offset, int count) {
  BVH::BVHNode *node = new BVH::BVHNode();
  node->box = box;
  node->prim_offset = offset;
  node->prim_count = count;
  node->left = nullptr;
  node->right = nullptr;
  return node;
}

BVH::BVHNode *init_node(BVH::BVHNode *left, BVH::BVHNode *right) {
  BVH::BVHNode *node = new BVH::BVHNode();
  node->box = left->box;
  node->box.expand(right->box);
  node->prim_offset = 0;
  node->prim_count = 0;
  node->left = left;
  node->right = right;
  return node;
}

BVH::BVHNode *BVH::recursive_build(int start, int end) {
  int p_count = end - start;
  if (p_count == 1) {
    ordered_primitives.push_back(primitives[start].p_ptr.get());
    return init_leaf(primitives[start].box, ordered_primitives.size() - 1, 1);
  } else {
    BBox bound;
    for (int i = start; i < end; i++) {
      bound.expand(primitives[i].box);
    }

    int dim = bound.maximum_extent();
    std::sort(primitives.begin() + start, primitives.begin() + end,
              [dim](const PrimitiveInfo &a, const PrimitiveInfo &b) -> bool {
                return a.center[dim] < b.center[dim];
              });
    int mid = start + (end - start) / 2;
    return init_node(recursive_build(start, mid), recursive_build(mid, end));
  }
}

void BVH::build() {
  std::cout << 0 << ' ' << primitives.size() << '\n';
  root = recursive_build(0, primitives.size());
};

void recursive_destroy(BVH::BVHNode *node) {
  if (node->left)
    recursive_destroy(node->left);
  if (node->right)
    recursive_destroy(node->right);
  delete node;
}

Intersection BVH::intersect(const Ray &ray) {
  std::stack<BVH::BVHNode *> s;
  Intersection res;

  s.push(root);
  while (!s.empty()) {
    auto node = s.top();
    s.pop();
    if (!node->right && !node->left) {
      auto intersection = ordered_primitives[node->prim_offset]->intersect(ray);
      if (intersection.hit && intersection.distance < res.distance)
        res = intersection;
    } else {
      auto l = node->left->box.intersect(ray);
      if (l.hit)
        s.push(node->left);
      auto r = node->right->box.intersect(ray);
      if (r.hit)
        s.push(node->right);
    }
  }
  return res;
}

Intersection BVH::rec_debug(BVH::BVHNode *node, const Ray &ray, int depth,
                            int i) {
  if (depth != i && (node->left || node->right)) {
    Intersection a, b;
    if (node->left)
      a = rec_debug(node->left, ray, depth, i + 1);
    if (node->right)
      b = rec_debug(node->right, ray, depth, i + 1);
    return a.distance < b.distance ? a : b;
  } else {
    return node->box.debug(ray);
  }
}

Intersection BVH::debug(const Ray &ray) {
  return rec_debug(root, ray, 100, 0);
}

BVH::~BVH() { recursive_destroy(root); }
