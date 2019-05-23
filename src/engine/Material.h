#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

enum PolygonMode
{
  POLYGON_MODE_POINTS = 0,
  POLYGON_MODE_LINES,
  POLYGON_MODE_FILL
};

enum LightingModel
{
  LIGHTING_MODEL_NONE = 0,
  LIGHTING_MODEL_FLAT,
  LIGHTING_MODEL_PHONG,
};

class Renderer;

class Material
{
public:
  Material();

  Material *clone();
  void bind(Renderer* renderer);

  glm::vec4 ambientColor;
  glm::vec4 diffuseColor;
  glm::vec4 specularColor;
  float opacity;

  PolygonMode polygonMode;
  LightingModel lightingModel;

  Texture *texture;
};
