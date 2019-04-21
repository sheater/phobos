#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.h"
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
  m_model = static_cast<Model *>(assetsMgr->getAsset(path));

  createBoundingBox();
}

ModelNode::~ModelNode()
{
  if (m_collisionHull)
    delete m_collisionHull;
}

void ModelNode::render()
{
  if (!m_model)
    return;

  glm::mat4 finalTransform = getAbsoluteTransform();

  SceneNode::render();
  m_model->render(finalTransform);
}

void ModelNode::createBoundingBox()
{
  BoundingBox *bbox = new BoundingBox();

  for (
      std::vector<Mesh *>::iterator it = m_model->m_meshes.begin();
      it != m_model->m_meshes.end();
      it++)
  {
    BoundingBox *other = (*it)->createBoundingBox();

    bbox->maybeExpand(other->m_absoluteMin);
    bbox->maybeExpand(other->m_absoluteMax);
  }

  m_collisionHull = bbox;
}
