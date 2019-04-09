#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Renderer.h"

Renderer::Renderer()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  GpuProgramFactory *programFactory = new GpuProgramFactory();
  programFactory->attachShader(Shader::createFromFile("shaders/main.vert", GL_VERTEX_SHADER));
  programFactory->attachShader(Shader::createFromFile("shaders/main.frag", GL_FRAGMENT_SHADER));
  m_baseProgram = programFactory->createProgram();
  delete programFactory;

  m_viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

Renderer::~Renderer()
{
  delete m_baseProgram;

  for (
      std::vector<VertexBuffer *>::iterator it = m_vertexBuffers.begin();
      it != m_vertexBuffers.end();
      it++)
  {
    delete *it;
  }
}

VertexBuffer *Renderer::createVertexBuffer(Geometry *geometry)
{
  VertexBuffer *vb = new VertexBuffer(geometry, this);
  m_vertexBuffers.push_back(vb);
  return vb;
}

typedef struct
{
  glm::vec3 position;
  glm::vec4 color;
} Light;

void Renderer::useBaseProgram(const glm::mat4 &modelMatrix, Material *material)
{
  m_baseProgram->use();

  const glm::mat4 modelInvTransMatrix = glm::inverse(glm::transpose(modelMatrix));

  m_baseProgram->setUniformMatrix("projectionMat", m_projectionMatrix);
  m_baseProgram->setUniformMatrix("viewMat", m_viewMatrix);
  m_baseProgram->setUniformMatrix("modelMat", modelMatrix);
  m_baseProgram->setUniformMatrix("modelInvTransMat", modelInvTransMatrix);

  Light light;

  light.position = glm::vec3(0.0f, 0.0f, 2.5f);
  light.color = glm::vec4(1.0f, 0.9f, 0.9f, 1.0f);

  m_baseProgram->setUniformVec3("lightPos", light.position);
  m_baseProgram->setUniformVec4("lightColor", light.color);

  glm::vec4 diffuseColor;
  GLenum polygonMode;
  if (material)
  {
    diffuseColor = material->diffuseColor;

    switch (material->polygonMode)
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
  }
  else
  {
    diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    polygonMode = GL_FILL;
  }

  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

  m_baseProgram->setUniformVec4("materialDiffuseColor", diffuseColor);
}

void Renderer::setViewport(unsigned int width, unsigned int height)
{
  m_width = width;
  m_height = height;
  m_projectionMatrix = glm::perspective(70.0f, (float)m_width / (float)m_height, 0.1f, 100.0f);

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
