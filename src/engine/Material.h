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
  Material()
      : ambientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f)),
        diffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        specularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        opacity(1.0f),
        texture(nullptr),
        polygonMode(POLYGON_MODE_FILL),
        lightingModel(LIGHTING_MODEL_PHONG) {}

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
