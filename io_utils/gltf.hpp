
#pragma once
#include "math/math.hpp"
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <assert.h>

namespace gltf {
  struct buffer {
    std::string name = "";
    int length;
    std::vector<std::byte> data;
  };

  struct buffer_view {
    int buffer;
    int offset;
    int length;
    int stride;
    int target;
    std::string name;
  };

  struct image {
    int bufferView_idx;
    std::string mimeType;
  };

  struct accessor {
    int buffer_view;
    int offset;
    std::string type;
    int component_type;
    int count;
    std::vector<double> min;
    std::vector<double> max;
  };

  struct primitive {
    int positions = -1;
    int normals = -1;
    int tangent = -1;
    int texcoord_0 = -1;
    int texcoord_1 = -1;
    int color_0 = -1;
    int joints_0 = -1;
    int weights_0 = -1;
    int indices;
    int material;
    int mode;
  };

  struct mesh {
    std::vector<primitive> primitives;
    std::string name;
  };

  struct scene {
    std::vector<int> nodes;
  };

  struct node {
    int object = -1;
    bool is_camera = false;
    std::vector<int> children;
    std::string name;
    std::array<float, 16> matrix;
  };
  
  class model {
  public:
    model(std::string_view file_name);
    int scene_index;
    std::vector<buffer> buffers;
    std::vector<buffer_view> buffer_views;
    std::vector<mesh> meshes;
    std::vector<scene> scenes;
    std::vector<node> nodes;
    std::vector<accessor> accessors;
  private:
  };
};
