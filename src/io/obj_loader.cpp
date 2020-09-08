#include "obj_loader.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <iostream>

std::vector<Vertex> parse_face(std::stringstream& ss, std::vector<vec3<float>>& positions, std::vector<vec3<float>>& normals) {
  enum ParseState{Position, Texture, Normal};
  std::vector<Vertex> vertices;
  std::string str;
  while (ss >> str) {
    Vertex v;
    std::stringstream vertex_stream(str);
    char c;
    int num = 0;
    int sign = 1;
    ParseState state = ParseState::Position;

    while (vertex_stream >> c) {
      switch(c) {
        case '-':
          sign = -1;
          break;
        case '/':
          num *= sign;
          switch (state) {
            case ParseState::Position:
              v.position = positions[num > 0 ? num - 1 : positions.size() + num];
              state = ParseState::Texture;
              break;
            case ParseState::Texture:
              state = ParseState::Normal;
              break;
            case ParseState::Normal:
              v.normal = normals[num > 0 ? num - 1 : positions.size() + num];
              break;
          }
          num = 0;
          sign = 1;
          break;
        default:
          num = num * 10 + (c - '0');
          break;
      }
    }
    num *= sign;
    std::cout << positions.size() << ' '<< positions.size() + num << '\n';
    switch (state) {
      case ParseState::Position:
        v.position = positions[num > 0 ? num - 1 : positions.size() + num];
        state = ParseState::Texture;
        break;
      case ParseState::Texture:
        state = ParseState::Normal;
        break;
      case ParseState::Normal:
        v.normal = normals[num > 0 ? num - 1 : positions.size() + num];
        break;
    }
    vertices.push_back(v);
  }

  vec3<float> normal = (positions[1] - positions[0]).cross(positions[2] - positions[0]).norm();
  for (auto& v : vertices) v.normal = normal;

  return vertices;
}

bool OBJ_Loader::parse_file(std::string_view fname) {
  std::ifstream input_file(fname.cbegin());

  std::string line;
  std::string str;
  std::vector<vec3<float>> positions;
  std::vector<vec3<float>> normals;
  std::vector<int> indices;
  while (std::getline(input_file, line)) {
    if (std::isspace(line[0]) || line[0] == '#' || line[0] == 's' || line[0] == 'u' || line[0] == 'm')
      continue;
    std::stringstream ss(line);
    std::cout << line << '\n';
    ss >> str;
    float x, y, z;
    if (str == "v") {
      ss >> x >> y >> z;
      std::cout << x << ' ' << y << ' ' << z << '\n';
      positions.push_back({x, y, z});
    } else if (str == "vn") {
      ss >> x >> y >> z;
      normals.push_back({x, y, z});
    } else if (str == "vt") {
      ss >> x >> y >> z;
    } else if (str == "f") {
      auto vertices = parse_face(ss, positions, normals);
      auto indices = std::vector<int>(vertices.size());
      std::iota(indices.begin(), indices.end(), meshes.back().indices.empty() ? 0 : meshes.back().indices.back() + 1);

      meshes.back().vertices.insert(meshes.back().vertices.end(), std::make_move_iterator(vertices.begin()), std::make_move_iterator(vertices.end()));
      meshes.back().indices.insert(meshes.back().indices.end(), std::make_move_iterator(indices.begin()), std::make_move_iterator(indices.end()));
      meshes.back().count++;
    } else if (str == "g") {
      meshes.push_back(Mesh());
      meshes.back().type = MeshType::quad;
      ss >> str;
      meshes.back().name = str;
    }
  }
  return true;
}
