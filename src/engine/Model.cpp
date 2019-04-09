#include <vector>

#include "Model.h"

void Model::render(const glm::mat4 &transformMatrix)
{
  for (
      std::vector<Mesh *>::iterator it = m_meshes.begin();
      it != m_meshes.end();
      it++)
  {
    (*it)->render(transformMatrix);
  }
}

void Model::addMesh(Mesh *mesh)
{
  m_meshes.push_back(mesh);
}
