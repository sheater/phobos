#pragma once

#include <string>
#include <vector>
#include <tinyxml2.h>

#include "Loader.h"

using namespace tinyxml2;

typedef struct
{
  glm::mat4 transformMatrix;
  std::string geometryId;
  std::string materialId;
} ColladaSceneNode;

typedef struct
{
  std::string id;
  Geometry *geometry;
} ColladaGeometry;

typedef struct
{
  std::string id;
  std::vector<float> floatArray;
} ColladaGeometrySource;

typedef struct
{
  std::string id;
  glm::vec4 diffuseColor;
} ColladaEffect;

typedef struct
{
  std::string id;
  ColladaEffect *effect;
} ColladaMaterial;

class ColladaLoader : public Loader
{
public:
  bool isSuitableExtension(const std::string &extension);
  virtual Asset *loadAsset(const std::string &path);

  inline void setPreprocessTransformMatrix(const glm::mat4 &matrix)
  {
    m_preprocessTransformMatrix = matrix;
  }

private:
  std::vector<ColladaGeometry> parseGeometries(XMLElement *rootEl);
  std::vector<ColladaSceneNode> parseSceneNodes(XMLElement *rootEl);
  std::vector<ColladaEffect> parseEffects(XMLElement *rootEl);
  std::vector<ColladaMaterial> parseMaterials(XMLElement *rootEl, std::vector<ColladaEffect> &effects);
  void parseSceneNode(XMLElement *parentEl, const glm::mat4 &transform, std::vector<ColladaSceneNode> &nodes);

  glm::mat4 m_preprocessTransformMatrix;
};
