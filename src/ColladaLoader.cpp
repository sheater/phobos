#include <sstream>

#include <tinyxml2.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ColladaLoader.h"
#include "Geometry.h"
#include "Model.h"

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

void processVisualSceneNode(XMLElement *parentEl, const glm::mat4 &transform, std::vector<ColladaSceneNode> &nodes)
{
  for (XMLElement *el = parentEl->FirstChildElement("node"); el; el = el->NextSiblingElement("node"))
  {
    glm::mat4 finalTransform(transform);
    XMLElement *matrixEl = el->FirstChildElement("matrix");
    if (matrixEl)
    {
      std::stringstream matrixStream(matrixEl->GetText());
      std::string segment;

      std::vector<float> matrixComponents;
      while (std::getline(matrixStream, segment, ' '))
      {
        matrixComponents.push_back(atof(segment.c_str()));
      }

      float *matrixPtr = &matrixComponents[0];
      finalTransform *= glm::transpose(glm::make_mat4(matrixPtr));
    }

    for (
        XMLElement *geometryInstEl = el->FirstChildElement("instance_geometry");
        geometryInstEl;
        geometryInstEl = geometryInstEl->NextSiblingElement("instance_geometry"))
    {
      ColladaSceneNode node;

      node.transformMatrix = finalTransform;
      node.geometryId = std::string(geometryInstEl->Attribute("url")).substr(1);

      XMLElement *bindMaterialEl = geometryInstEl->FirstChildElement("bind_material");
      XMLElement *techniqueCommonEl = bindMaterialEl->FirstChildElement("technique_common");
      XMLElement *instanceMaterialEl = techniqueCommonEl->FirstChildElement("instance_material");

      node.materialId = std::string(instanceMaterialEl->Attribute("target")).substr(1);

      nodes.push_back(node);
    }

    processVisualSceneNode(el, finalTransform, nodes);
  }
}

bool ColladaLoader::isSuitableExtension(const std::string &extension)
{
  return extension == "dae";
}

Asset *ColladaLoader::loadAsset(const std::string &path)
{
  XMLDocument doc;
  doc.LoadFile(path.c_str());

  XMLElement *rootEl = doc.RootElement();

  // --------------------
  // Geometries
  XMLElement *geometriesEl = rootEl->FirstChildElement("library_geometries");

  std::vector<ColladaGeometry> geometries;
  for (XMLElement *geometryEl = geometriesEl->FirstChildElement(); geometryEl; geometryEl = geometryEl->NextSiblingElement())
  {
    ColladaGeometry geometry;
    geometry.id = geometryEl->Attribute("id");

    XMLElement *meshEl = geometryEl->FirstChildElement("mesh");

    std::vector<ColladaGeometrySource> sources;
    for (XMLElement *sourceEl = meshEl->FirstChildElement("source"); sourceEl; sourceEl = sourceEl->NextSiblingElement("source"))
    {
      XMLElement *floatArrayEl = sourceEl->FirstChildElement("float_array");

      std::stringstream floatArrayStream(floatArrayEl->GetText());
      std::string segment;
      ColladaGeometrySource source;

      source.id = sourceEl->Attribute("id");

      while (std::getline(floatArrayStream, segment, ' '))
      {
        source.floatArray.push_back(atof(segment.c_str()));
      }

      sources.push_back(source);
    }

    geometry.geometry = new Geometry();

    XMLElement *verticesEl = meshEl->FirstChildElement("vertices");
    for (XMLElement *inputEl = verticesEl->FirstChildElement(); inputEl; inputEl = inputEl->NextSiblingElement())
    {
      std::vector<glm::vec3> *target = nullptr;
      std::string semantic = std::string(inputEl->Attribute("semantic"));

      if (semantic == "POSITION")
      {
        target = &geometry.geometry->positions;
      }
      else if (semantic == "NORMAL")
      {
        target = &geometry.geometry->normals;
      }
      else
      {
        throw std::runtime_error(std::string("Unknown semantic: ") + semantic);
      }

      std::string source = std::string(inputEl->Attribute("source")).substr(1);
      ColladaGeometrySource *sourcePtr = nullptr;

      for (std::vector<ColladaGeometrySource>::iterator it = sources.begin(); it != sources.end(); it++)
      {
        if (it->id == source)
        {
          sourcePtr = &*it;
          break;
        }
      }

      if (!sourcePtr)
      {
        throw std::runtime_error(std::string("Unknown source: ") + source);
      }

      for (std::vector<float>::iterator it = sourcePtr->floatArray.begin(); it != sourcePtr->floatArray.end();)
      {
        target->push_back({*it++, *it++, *it++});
      }
    }

    std::vector<unsigned int> indices;
    XMLElement *trianglesEl = meshEl->FirstChildElement("triangles");
    if (trianglesEl)
    {
      XMLElement *pEl = trianglesEl->FirstChildElement("p");

      std::stringstream arrayStream(pEl->GetText());
      std::string segment;

      while (std::getline(arrayStream, segment, ' '))
      {
        geometry.geometry->indices.push_back(atoi(segment.c_str()));
      }
    }

    geometries.push_back(geometry);
  }

  // --------------------
  // Visual scene
  XMLElement *visualScenesEl = rootEl->FirstChildElement("library_visual_scenes");
  XMLElement *visualSceneEl = visualScenesEl->FirstChildElement("visual_scene");

  std::vector<ColladaSceneNode> nodes;
  processVisualSceneNode(visualSceneEl, glm::mat4(1.0f), nodes);
  // XMLElement *libraryNodesEl = rootEl->FirstChildElement("library_nodes");
  // processVisualSceneNode(libraryNodesEl, glm::mat4(1.0f), nodes);

  // --------------------
  // Effects
  std::vector<ColladaEffect> effects;
  XMLElement *libraryEffectsEl = rootEl->FirstChildElement("library_effects");
  for (
      XMLElement *effectEl = libraryEffectsEl->FirstChildElement("effect");
      effectEl;
      effectEl = effectEl->NextSiblingElement("effect"))
  {
    ColladaEffect effect;

    effect.id = std::string(effectEl->Attribute("id"));

    XMLElement *profileEl = effectEl->FirstChildElement("profile_COMMON");
    XMLElement *techniqueEl = profileEl->FirstChildElement("technique");

    XMLElement *lambertEl = techniqueEl->FirstChildElement("lambert");
    XMLElement *diffuseEl = lambertEl->FirstChildElement("diffuse");

    XMLElement *colorEl = diffuseEl->FirstChildElement("color");
    if (colorEl)
    {
      std::stringstream colorStream(colorEl->GetText());
      std::string segment;
      std::vector<float> colorComponents;

      while (std::getline(colorStream, segment, ' '))
      {
        colorComponents.push_back(atof(segment.c_str()));
      }

      effect.diffuseColor = glm::vec4(glm::make_vec4(&colorComponents[0]));
    }
    else
    {
      effect.diffuseColor = glm::vec4(1.0f);
    }

    XMLElement *textureEl = diffuseEl->FirstChildElement("texture");
    if (textureEl)
    {
      // TODO: add texture
    }

    effects.push_back(effect);
  }

  // --------------------
  // Materials
  std::vector<ColladaMaterial> materials;
  XMLElement *libraryMaterialsEl = rootEl->FirstChildElement("library_materials");
  for (
      XMLElement *materialEl = libraryMaterialsEl->FirstChildElement("material");
      materialEl;
      materialEl = materialEl->NextSiblingElement("material"))
  {
    ColladaMaterial material;

    material.id = materialEl->Attribute("id");
    material.effect = nullptr;

    XMLElement *instanceEffectEl = materialEl->FirstChildElement("instance_effect");
    std::string effectId = std::string(instanceEffectEl->Attribute("url")).substr(1);

    for (std::vector<ColladaEffect>::iterator it = effects.begin(); it != effects.end(); it++)
    {
      if (it->id == effectId)
      {
        material.effect = &*it;
        break;
      }
    }

    if (material.effect)
    {
      materials.push_back(material);
    }
  }

  // --------------------
  // Model creation
  Model *model = new Model();

  for (std::vector<ColladaSceneNode>::iterator it = nodes.begin(); it != nodes.end(); it++)
  {
    Mesh *mesh = new Mesh();
    Geometry *geometry = nullptr;

    for (
        std::vector<ColladaGeometry>::iterator geometryIt = geometries.begin();
        geometryIt != geometries.end();
        geometryIt++)
    {
      if (geometryIt->id == it->geometryId)
      {
        geometry = geometryIt->geometry;
        break;
      }
    }

    if (!geometry)
    {
      throw std::runtime_error(std::string("Unable to find geometry with ID: ") + it->geometryId);
    }

    mesh->vertexBuffer = m_assetsMgr->getRenderer()->createVertexBuffer(geometry);
    mesh->transform = it->transformMatrix;

    ColladaMaterial* materialPtr = nullptr;
    for (
      std::vector<ColladaMaterial>::iterator materialIt = materials.begin();
      materialIt != materials.end();
      materialIt++)
    {
      std::cout << "it: " << it->materialId << "; mat: " << materialIt->id << std::endl;
      if (it->materialId == materialIt->id)
      {
        materialPtr = &*materialIt;
        break;
      }
    }

    if (materialPtr)
    {
      std::cout << "KOKOKT" << std::endl;
      mesh->material = new Material();
      mesh->material->diffuseColor = materialPtr->effect->diffuseColor;
    }

    model->addMesh(mesh);
  }

  // TODO: library_images

  return model;
}
