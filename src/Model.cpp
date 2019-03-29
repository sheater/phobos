#include <vector>

#include "Model.h"

void Model::render(const glm::mat4 &matrix)
{
  for (
      std::vector<Mesh *>::iterator it = m_meshes.begin();
      it != m_meshes.end();
      it++)
  {
    (*it)->render(matrix);
  }
}

void Model::addMesh(Mesh *mesh)
{
  m_meshes.push_back(mesh);
}
