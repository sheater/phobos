#include <string>
#include <vector>

#include "Mesh.h"
#include "Asset.h"

class Model : public Asset
{
public:
  void render(const glm::mat4x4& matrix);
  void addMesh(Mesh* mesh);

private:
  std::vector<Mesh *> m_meshes;
};
