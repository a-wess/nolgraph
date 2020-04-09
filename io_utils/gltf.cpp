#include "gltf.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>

const int BASE64_HEADER_LENGTH = 37;

uint32_t b64_to_b(char c) {
  if (c == '+') return 62;
  if (c == '/') return 63;
  if (c > 'Z') return c - 8 - 'A';
  else return c - 'A';
};

namespace gltf {
  buffer get_buffer(const json::object& buffer_object) {
    buffer b;
    if (buffer_object.has_key("name")) b.name = buffer_object["name"].get_string();
    b.length = buffer_object["byteLength"].get_int();
    auto uri = buffer_object["uri"].get_string();

    if (uri.size() > BASE64_HEADER_LENGTH && uri.substr(0, BASE64_HEADER_LENGTH) == "data:application/octet-stream;base64,") {
      b.data.reserve(b.length);
      for (auto i = BASE64_HEADER_LENGTH; i < uri.size(); i += 4) {
        uint32_t bytes = b64_to_b(uri[i]) << 18
          | b64_to_b(uri[i + 1]) << 12
          | b64_to_b(uri[i + 1]) << 6
          | b64_to_b(uri[i + 3]);
        b.data.push_back(std::byte(static_cast<char>(bytes >> 16)));
        b.data.push_back(std::byte(static_cast<char>(bytes >> 8)));
        b.data.push_back(std::byte(static_cast<char>(bytes)));
      }
    } else {

    }
    std::cout << "Buffer size test: " << ((b.data.size() == b.length) ? "True\n" : "False\n");
    return b;
  }

  model::model(std::string_view file_name) {
    const auto text = json::parse_file(file_name);
    std::cout << "JSON parsing completed\n";
    //Buffer
    for (auto& buffer_text : text["buffers"].get_array()) {
      std::cout << "Pushing Buffer\n";
      buffers.push_back(get_buffer(buffer_text.get_object()));
    }
    std::cout << "Proccessed buffers\n";
    //Buffer views
    for (auto& view_text : text["bufferViews"].get_array()) {
      buffer_view bv;
      if (view_text.get_object().has_key("name")) bv.name = view_text["name"].get_string();
      if (view_text.get_object().has_key("byteOffset")) bv.offset = view_text["byteOffset"].get_int();
      if (view_text.get_object().has_key("byteStride")) bv.offset = view_text["byteStride"].get_int();
      if (view_text.get_object().has_key("target")) bv.target = view_text["target"].get_int();
      bv.buffer = view_text["buffer"].get_int();
      bv.length = view_text["byteLength"].get_int();
      buffer_views.push_back(bv);
    }
    std::cout << "Proccessed BufferViews\n";
    // Accessors
    for (auto& accessor_text: text["accessors"].get_array()) {
      accessor a;
      a.buffer_view = accessor_text["bufferView"].get_int();
      a.offset = accessor_text["byteOffset"].get_int();
      a.type = accessor_text["type"].get_string();
      a.component_type = accessor_text["componentType"].get_int();
      a.count = accessor_text["count"].get_int();
      for (auto& m : accessor_text["min"].get_array()) {
	//assert(m.is_float());
	double val = m.is_float() ? m.get_float() : m.get_int();
	a.min.push_back(val);
      }
      for (auto& m : accessor_text["max"].get_array()) {
	double val = m.is_float() ? m.get_float() : m.get_int();
	a.max.push_back(val);
      }
      accessors.push_back(a);
    }
    std::cout << "Proccessed accessors\n";
    // Meshes
    for (auto& mesh_text : text["meshes"].get_array()) {
      mesh m;
      for (auto& primitive_text : mesh_text["primitives"].get_array()) {
        primitive p;
	auto& attributes = primitive_text["attributes"].get_object();
        p.positions = attributes["POSITION"].get_int();
        p.normals = attributes.has_key("NORMAL") ? attributes["NORMAL"].get_int() : -1;
	p.tangent = attributes.has_key("TANGENT") ? attributes["NORMAL"].get_int() : -1;
	p.texcoord_0 = attributes.has_key("TEXCOORD_0") ? attributes["TEXCOORD_0"].get_int() : -1;
	p.texcoord_1 = attributes.has_key("TEXCOORD_1") ? attributes["TEXCOORD_1"].get_int() : -1;
	p.color_0 = attributes.has_key("COLOR_0") ? attributes["COLOR_0"].get_int() : -1;
	p.joints_0 = attributes.has_key("JOINTS_0") ? attributes["JOINTS_0"].get_int() : -1;
	p.weights_0 = attributes.has_key("WEIGHTS_0") ? attributes["WEIGHTS_0"].get_int() : -1;
	p.indices = primitive_text["indices"].get_int();
	p.material = primitive_text["material"].get_int();
	p.mode = primitive_text["mode"].get_int();
        m.primitives.push_back(std::move(p));
      }
      m.name = mesh_text["name"].get_string();
      meshes.push_back(std::move(m));
    }
    std::cout << "Proccessed meshes\n";
    //Scenes
    for (auto& scene_text : text["scenes"].get_array()) {
      scene s;
      for (auto& n : scene_text["nodes"].get_array()) s.nodes.push_back(n.get_int());
    }
    std::cout << "Proccessed scenes\n";
    //Nodes
    for (auto& node_text: text["nodes"].get_array()) {
      node n;
      if (node_text.get_object().has_key("camera")) {
        n.object = node_text["camera"].get_int();
        n.is_camera = true;
      } else if (node_text.get_object().has_key("mesh")) {
        n.object = node_text["mesh"].get_int();
      }
      if (node_text.get_object().has_key("matrix")) {
	auto& mat = node_text["matrix"].get_array();
	for (std::size_t i = 0; i < mat.size(); i++) {
	  n.matrix[i] = mat[i].is_int() ? static_cast<float>(mat[i].get_int()) : mat[i].get_float();
	}
      }
      if (node_text.get_object().has_key("children")) {
	for (auto& c : node_text["children"].get_array())
	  n.children.push_back(c.get_int());
      }
      if (node_text.get_object().has_key("name"))
	n.name = node_text["name"].get_string();
      nodes.push_back(std::move(n));
    }
    std::cout << "Proccessed nodes\n";
  }
};

/*int main() {
  gltf::model m("Box.gltf");
  return 0;
}*/

