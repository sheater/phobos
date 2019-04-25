#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
#include "MeshNode.h"
#include "ModelNode.h"
#include "BoundingBox.h"
#include "ColladaLoader.h"

ModelNode::ModelNode(
    Scene *scene,
    const std::string &path,
    const glm::mat4 &preprocessTransformMatrix)
    : SceneNode(scene)
{
  AssetsManager *assetsMgr = getScene()->getAssetsManager();
  ColladaLoader *loader = static_cast<ColladaLoader *>(assetsMgr->getLoader(path));

  loader->setPreprocessTransformMatrix(preprocessTransformMatrix);
  Model *model = static_cast<Model *>(assetsMgr->getAsset(path));

  // FIXME: another collision hull types
  m_collisionHull = new BoundingBox();

  for (
      std::vector<Mesh *>::iterator it = model->meshes.begin();
      it != model->meshes.end();
      it++)
  {
    MeshNode *node = new MeshNode(*it, scene);
    attachNode(node);
  }
}

ModelNode::~ModelNode()
{
  if (m_collisionHull)
    delete m_collisionHull;
}

void ModelNode::update(float timeDelta)
{
  SceneNode::update(timeDelta);

  if (m_collisionHull) {
    m_collisionHull->reset();

    for (
        std::vector<SceneNode *>::iterator it = m_nodes.begin();
        it != m_nodes.end();
        it++)
    {
      CollisionHull* hull = (*it)->getCollisionHull();
      if (!hull)
        continue;

      m_collisionHull->expandByCollisionHull(hull);
    }
  }
}
