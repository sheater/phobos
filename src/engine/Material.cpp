#include "Material.h"
#include "Renderer.h"

Material *Material::clone()
{
  Material *c = new Material();

  c->ambientColor = ambientColor;
  c->diffuseColor = diffuseColor;
  c->specularColor = specularColor;

  c->polygonMode = polygonMode;
  c->lightingModel = lightingModel;

  c->texture = texture;

  return c;
}

void Material::bind(Renderer* renderer)
{
  GpuProgramType programType = GPU_PROGRAM_NO_SHADING;

  switch (lightingModel)
  {
    case LIGHTING_MODEL_FLAT:
      programType = GPU_PROGRAM_FLAT_SHADING;
      break;

    case LIGHTING_MODEL_PHONG:
      programType = GPU_PROGRAM_PHONG_SHADING;
      break;
  }

  GpuProgram* program = renderer->bindGpuProgram(programType);

  program->setUniformFloat("opacity", opacity);

  if (lightingModel == LIGHTING_MODEL_FLAT || lightingModel == LIGHTING_MODEL_PHONG)
  {
    program->setUniformVec4("materialAmbientColor", ambientColor);
    program->setUniformVec4("materialDiffuseColor", diffuseColor);
  }

  if (lightingModel == LIGHTING_MODEL_PHONG)
  {
    program->setUniformVec4("materialSpecularColor", specularColor);
  }

  GLenum polygonMode = GL_FILL;

  switch (polygonMode)
  {
  case POLYGON_MODE_POINTS:
    polygonMode = GL_POINT;
    break;

  case POLYGON_MODE_LINES:
    polygonMode = GL_LINE;
    break;

  case POLYGON_MODE_FILL:
    polygonMode = GL_FILL;
    break;
  }

  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}
