#pragma once

#include "Mesh.h"
#include "SceneNode.h"

class MeshNode : public SceneNode
{
public:
  MeshNode(Mesh *mesh, Scene *scene);

  void render();
  void update(float timeDelta);

  Material *material;

private:  
  Mesh *m_originalMesh;
};
