#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <iostream>

#include "Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  setViewport(width, height);

  loadGpuProgram(GPU_PROGRAM_NO_SHADING, "shaders/noShading");
  loadGpuProgram(GPU_PROGRAM_FLAT_SHADING, "shaders/flatShading");
  loadGpuProgram(GPU_PROGRAM_PHONG_SHADING, "shaders/phongShading");
  loadGpuProgram(GPU_PROGRAM_PARTICLES, "shaders/particles");
  loadGpuProgram(GPU_PROGRAM_UI, "shaders/ui");

  m_viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
  m_currentGpuProgram = nullptr;
  // FIXME: default light
  m_currentLight = new Light();
}

Renderer::~Renderer()
{
  if (m_currentLight)
    delete m_currentLight;

  for (
      std::vector<VertexBuffer *>::iterator it = m_vertexBuffers.begin();
      it != m_vertexBuffers.end();
      it++)
  {
    delete *it;
  }

  for (
      std::map<GpuProgramType, GpuProgram *>::iterator it = m_gpuPrograms.begin();
      it != m_gpuPrograms.end();
      it++)
  {
    delete it->second;
  }
}

VertexBuffer *Renderer::createVertexBuffer(Geometry *geometry)
{
  VertexBuffer *vb = new VertexBuffer(geometry, this);
  m_vertexBuffers.push_back(vb);
  return vb;
}

void Renderer::removeVertexBuffer(VertexBuffer *vertexBuffer)
{
  std::vector<VertexBuffer *>::iterator it = std::find(
      m_vertexBuffers.begin(),
      m_vertexBuffers.end(),
      vertexBuffer);

  if (it != m_vertexBuffers.end())
  {
    delete *it;
    m_vertexBuffers.erase(it);
  }
}

GpuProgram *Renderer::bindGpuProgram(GpuProgramType type)
{
  std::map<GpuProgramType, GpuProgram *>::iterator it = m_gpuPrograms.find(type);
  if (it == m_gpuPrograms.end())
    throw std::runtime_error("Unable to find GPU program");

  m_currentGpuProgram = it->second;

  m_currentGpuProgram->use();

  m_currentGpuProgram->setUniformMatrix("projectionMat", m_projectionMatrix);
  m_currentGpuProgram->setUniformMatrix("viewMat", m_viewMatrix);

  switch (type)
  {
  case GPU_PROGRAM_NO_SHADING:
    break;

  case GPU_PROGRAM_FLAT_SHADING:
  case GPU_PROGRAM_PHONG_SHADING:
    m_currentGpuProgram->setUniformVec3("lightPos", m_currentLight->position);
    m_currentGpuProgram->setUniformVec4("lightColor", m_currentLight->color);

    break;

  case GPU_PROGRAM_PARTICLES:
    break;

  case GPU_PROGRAM_UI:
    break;
  }

  return m_currentGpuProgram;
}

void Renderer::loadGpuProgram(GpuProgramType type, const std::string &path)
{
  GpuProgramFactory *programFactory = new GpuProgramFactory();

  Shader *vertexShader = Shader::createFromFile(path + "/vertex.glsl", GL_VERTEX_SHADER);
  Shader *fragmentShader = Shader::createFromFile(path + "/fragment.glsl", GL_FRAGMENT_SHADER);

                               programFactory->attachShader(vertexShader);
  programFactory->attachShader(fragmentShader);

  GpuProgram *program = programFactory->createProgram();
  m_gpuPrograms.insert(std::pair<GpuProgramType, GpuProgram *>(type, program));

  delete programFactory;
}

// void Renderer::useBaseProgram(const glm::mat4 &modelMatrix, Material *material)
// {
//   m_baseProgram->use();

//   const glm::mat4 modelInvTransMatrix = glm::inverse(glm::transpose(modelMatrix));

//   m_baseProgram->setUniformMatrix("projectionMat", m_projectionMatrix);
//   m_baseProgram->setUniformMatrix("viewMat", m_viewMatrix);
//   m_baseProgram->setUniformMatrix("modelMat", modelMatrix);
//   m_baseProgram->setUniformMatrix("modelInvTransMat", modelInvTransMatrix);

//   glm::vec4 diffuseColor;
//   GLenum polygonMode;
//   if (material)
//   {
//     diffuseColor = material->diffuseColor;

//     switch (material->polygonMode)
//     {
//     case POLYGON_MODE_POINTS:
//       polygonMode = GL_POINT;
//       break;

//     case POLYGON_MODE_LINES:
//       polygonMode = GL_LINE;
//       break;

//     case POLYGON_MODE_FILL:
//       polygonMode = GL_FILL;
//       break;
//     }
//   }
//   else
//   {
//     diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//     polygonMode = GL_FILL;
//   }

//   glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

//   m_baseProgram->setUniformVec4("materialDiffuseColor", diffuseColor);
// }

void Renderer::updateProjectionMatrix()
{
  switch (m_projectionType)
  {
  case PROJECTION_TYPE_PERSPECTIVE:
    m_projectionMatrix = glm::perspective(
        70.0f,
        (float)m_width / (float)m_height,
        0.1f,
        100.0f);
    break;

  case PROJECTION_TYPE_ORTHO:
    m_projectionMatrix = glm::ortho(
        0.0f,
        static_cast<float>(m_width),
        static_cast<float>(m_height),
        0.0f,
        0.0f,
        100.0f);
    break;
  }
}

void Renderer::setViewport(unsigned int width, unsigned int height)
{
  m_width = width;
  m_height = height;
  updateProjectionMatrix();

  glViewport(0, 0, m_width, m_height);
}

void Renderer::clearBuffers()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::flush()
{
  glFlush();

  checkError();
}

void Renderer::setModelViewMatrix(const glm::mat4 &matrix)
{
  if (m_currentGpuProgram)
  {
    const glm::mat4 invTransMatrix = glm::inverse(glm::transpose(matrix));

    m_currentGpuProgram->setUniformMatrix("modelMat", matrix);
    m_currentGpuProgram->setUniformMatrix("modelInvTransMat", invTransMatrix);
  }
}

void Renderer::checkError()
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    std::string errorMsg = "unknown";

    switch (error)
    {
    case GL_INVALID_ENUM:
      errorMsg = "GL_INVALID_ENUM";
      break;

    case GL_INVALID_VALUE:
      errorMsg = "GL_INVALID_VALUE";
      break;

    case GL_INVALID_OPERATION:
      errorMsg = "GL_INVALID_OPERATION";
      break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errorMsg = "GL_INVALID_FRAMEBUFFER_OPERATION";
      break;

    case GL_OUT_OF_MEMORY:
      errorMsg = "GL_OUT_OF_MEMORY";
      break;

    case GL_STACK_UNDERFLOW:
      errorMsg = "GL_STACK_UNDERFLOW";
      break;

    case GL_STACK_OVERFLOW:
      errorMsg = "GL_STACK_OVERFLOW";
      break;
    }
    std::cerr << "OpenGL error: " << errorMsg << std::endl;
  }
}
