#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <iostream>

#include "Renderer.h"

Renderer::Renderer(unsigned int width, unsigned int height) : m_currentGpuProgram(nullptr)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  setViewport(width, height);

  m_viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

  loadGpuPrograms();
  createLightBufferObject();
}

Renderer::~Renderer()
{
  deleteLightBufferObject();

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

#define MAX_LIGHTS 24
#define LIGHTS_UBO_SIZE 16 + 16 * 2 * MAX_LIGHTS

void Renderer::addLight(Light *light)
{
  if (m_lights.size() == MAX_LIGHTS - 1)
    return;

  m_lights.push_back(light);
}

void Renderer::removeLight(const Light *light)
{
  std::vector<Light *>::iterator it = std::find(m_lights.begin(), m_lights.end(), light);
  if (it != m_lights.end())
  {
    m_lights.erase(it);
  }
}

void Renderer::createLightBufferObject()
{
  glGenBuffers(1, &m_lightBufferObject);
  glBindBuffer(GL_UNIFORM_BUFFER, m_lightBufferObject);
  glBufferData(GL_UNIFORM_BUFFER, LIGHTS_UBO_SIZE, nullptr, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_lightBufferObject);
}

void Renderer::deleteLightBufferObject()
{
  for (
      std::vector<Light *>::iterator it = m_lights.begin();
      it != m_lights.end();
      it++)
  {
    delete *it;
  }

  glDeleteBuffers(1, &m_lightBufferObject);
}

void Renderer::updateLightBufferObject()
{
  int numLights = m_lights.size();

  glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
  glm::vec3 position = glm::vec3(0.0f);

  glBindBuffer(GL_UNIFORM_BUFFER, m_lightBufferObject);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, 4, &numLights);
  for (int i = 0; i < m_lights.size(); i++)
  {
    int offset = 16 + i * sizeof(Light);
    Light* light = m_lights[i];

    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(Light), light);
  }
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

  return m_currentGpuProgram;
}

void Renderer::loadGpuPrograms()
{
  loadGpuProgram(GPU_PROGRAM_NO_SHADING, "shaders/noShading");
  loadGpuProgram(GPU_PROGRAM_PARTICLES, "shaders/particles");
  loadGpuProgram(GPU_PROGRAM_UI, "shaders/ui");
  GpuProgram *flatShadingProgram = loadGpuProgram(GPU_PROGRAM_FLAT_SHADING, "shaders/flatShading");
  GpuProgram *phongShadingProgram = loadGpuProgram(GPU_PROGRAM_PHONG_SHADING, "shaders/phongShading");

  flatShadingProgram->setBindingPoint("lightData", 0);
  phongShadingProgram->setBindingPoint("lightData", 0);
}

GpuProgram *Renderer::loadGpuProgram(GpuProgramType type, const std::string &path)
{
  GpuProgramFactory *programFactory = new GpuProgramFactory();

  Shader *vertexShader = Shader::createFromFile(path + "/vertex.glsl", GL_VERTEX_SHADER);
  Shader *fragmentShader = Shader::createFromFile(path + "/fragment.glsl", GL_FRAGMENT_SHADER);

  programFactory->attachShader(vertexShader);
  programFactory->attachShader(fragmentShader);

  GpuProgram *program = programFactory->createProgram();
  m_gpuPrograms.insert(std::pair<GpuProgramType, GpuProgram *>(type, program));

  delete programFactory;

  return program;
}

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

  updateLightBufferObject();
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
