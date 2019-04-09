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
  LIGHTING_MODEL_BASIC,
  LIGHTING_MODEL_PHONG,
};

class Material
{
public:
  Material()
      : diffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        texture(nullptr),
        polygonMode(POLYGON_MODE_FILL),
        lightingModel(LIGHTING_MODEL_BASIC) {}

  glm::vec4 ambientColor;
  glm::vec4 diffuseColor;
  glm::vec4 specularColor;

  PolygonMode polygonMode;
  LightingModel lightingModel;

  Texture *texture;
};
