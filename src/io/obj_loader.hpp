#ifndef _RAYS_OBJ_LOADER_
#define _RAYS_OBJ_LOADER_
#include <core/mesh.hpp>

class OBJ_Loader {
public:
  bool parse_file(std::string_view fname);
  std::vector<Mesh> &get_meshes() { return meshes; };

private:
  std::vector<Mesh> meshes;
};

#endif