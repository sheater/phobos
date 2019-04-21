#pragma once

#include "Mesh.h"
#include "SceneNode.h"

class MeshNode : public SceneNode
{
public:
  MeshNode(Mesh *mesh, Scene *scene);

  void render();
  void update(float timeDelta);

private:
  Material *m_material;
  Mesh *m_originalMesh;
};
