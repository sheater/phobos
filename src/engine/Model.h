#include <string>
#include <vector>

#include "Mesh.h"
#include "Asset.h"

class Model : public Asset
{
public:
  void render(const glm::mat4 &transformMatrix);
  void addMesh(Mesh* mesh);

// private:
  std::vector<Mesh *> m_meshes;
};
