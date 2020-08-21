#include "obj_loader.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

bool OBJ_Loader::parse_file(std::string_view fname) {
  std::ifstream input_file(fname.cbegin());

  std::string line;
  std::string str;
  std::vector<vec3<float>> positions;
  std::vector<vec3<float>> normals;
  std::vector<int> indices;
  while (std::getline(input_file, line)) {
    if (line[0] == '#' || line[0] == 's' || line[0] == 'u' || line[0] == 'm')
      continue;
    std::stringstream ss(line);
    ss >> str;
    float x, y, z;
    if (str == "v") {
      ss >> x >> y >> z;
      positions.push_back({x, y, z});
    } else if (str == "vn") {
      ss >> x >> y >> z;
      normals.push_back({x, y, z});
    } else if (str == "vt") {
      ss >> x >> y >> z;
    } else if (str == "f") {
      while (ss >> str) {
        auto &vertices = meshes.back().vertices;
        int p, n;
        char c;
        std::stringstream face(str);
        face >> p >> c >> c >> n;
        auto it = std::find_if(vertices.begin(), vertices.end(),
                               [p, n, positions, normals](Vertex &v) {
                                 return v.position == positions[p - 1] &&
                                        v.normal == normals[n - 1];
                               });
        if (vertices.empty() || it == vertices.end()) {
          vertices.push_back({positions[p - 1], normals[n - 1]});
          meshes.back().indices.push_back(vertices.size() - 1);
        } else {
          meshes.back().indices.push_back(std::distance(vertices.begin(), it));
        }
      }
      meshes.back().count++;
    } else if (str == "o") {
      meshes.push_back(Mesh());
      meshes.back().type = MeshType::triangle;
      ss >> str;
      meshes.back().name = str;
    }
  }
  return true;
}
