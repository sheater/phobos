#pragma once

#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <map>

#include "GpuProgram.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Light.h"

enum ProjectionType
{
  PROJECTION_TYPE_PERSPECTIVE = 0,
  PROJECTION_TYPE_ORTHO
};

enum GpuProgramType
{
  GPU_PROGRAM_NO_SHADING = 0,
  GPU_PROGRAM_FLAT_SHADING,
  GPU_PROGRAM_PHONG_SHADING,
  GPU_PROGRAM_PARTICLES,
  GPU_PROGRAM_UI
};

class Renderer
{
public:
  Renderer(unsigned int width, unsigned int height);
  ~Renderer();

  void useBaseProgram(const glm::mat4 &modelMatrix, Material *material);
  void setViewport(unsigned int width, unsigned int height);

  VertexBuffer *createVertexBuffer(Geometry *geometry);
  void removeVertexBuffer(VertexBuffer *vertexBuffer);
  Texture *createTexture(unsigned int width, unsigned int height, void *pixels);

  void clearBuffers();
  void flush();

  inline unsigned int getWidth() { return m_width; }
  inline unsigned int getHeight() { return m_height; }
  inline glm::mat4 getProjectionMatrix() { return m_projectionMatrix; }
  inline glm::mat4 getViewMatrix() { return m_viewMatrix; }
  void setModelViewMatrix(const glm::mat4 &matrix);
  void addLight(Light *light);
  void removeLight(const Light *light);

  GpuProgram *bindGpuProgram(GpuProgramType type);

  inline void setProjectionType(ProjectionType type)
  {
    m_projectionType = type;
    updateProjectionMatrix();
  }

private:
  void checkError();
  void updateProjectionMatrix();
  void createLightBufferObject();
  void deleteLightBufferObject();
  void updateLightBufferObject();
  void loadGpuPrograms();
  GpuProgram *loadGpuProgram(GpuProgramType type, const std::string &path);

  GLuint m_lightBufferObject;

  unsigned int m_width;
  unsigned int m_height;
  ProjectionType m_projectionType;
  glm::mat4x4 m_projectionMatrix;
  glm::mat4x4 m_viewMatrix;

  std::vector<VertexBuffer *> m_vertexBuffers;
  std::map<GpuProgramType, GpuProgram *> m_gpuPrograms;
  GpuProgram *m_currentGpuProgram;
  std::vector<Light *> m_lights;
};
