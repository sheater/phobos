#include <stddef.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Renderer *renderer) : m_renderer(renderer)
{
  loadGpuProgram();
  createArrayObject();
}

void ParticleSystem::loadGpuProgram()
{
  GpuProgramFactory *programFactory = new GpuProgramFactory();
  programFactory->attachShader(Shader::createFromFile("shaders/particle.vert", GL_VERTEX_SHADER));
  programFactory->attachShader(Shader::createFromFile("shaders/particle.frag", GL_FRAGMENT_SHADER));
  m_gpuProgram = programFactory->createProgram();
  delete programFactory;
}

void ParticleSystem::createArrayObject()
{
  glm::vec3 positions[] = {
      glm::vec3{-1.0f, 1.0f, 0.0f},
      glm::vec3{1.0f, 1.0f, 0.0f},
      glm::vec3{1.0f, -1.0f, 0.0f},
      glm::vec3{-1.0f, -1.0f, 0.0f},
  };

  glm::vec2 texcoords[] = {
      glm::vec2{0.0f, 1.0f},
      glm::vec2{1.0f, 1.0f},
      glm::vec2{1.0f, 0.0f},
      glm::vec2{0.0f, 0.0f},
  };

  GLuint indices[] = {
      0, 1, 2,
      2, 3, 0};

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  GLuint vbo, ibo = 0;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  unsigned int positionsSize = sizeof(positions);
  unsigned int texcoordsSize = sizeof(texcoords);
  unsigned int totalSize = positionsSize + texcoordsSize;
  glBufferData(GL_ARRAY_BUFFER, totalSize, 0, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &positions[0]);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBufferSubData(GL_ARRAY_BUFFER, positionsSize, texcoordsSize, &texcoords[0]);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(positionsSize));
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);
}

ParticleSystem::~ParticleSystem()
{
  for (
      std::vector<Particle *>::iterator it = m_particles.begin();
      it != m_particles.end();
      it++)
  {
    delete *it;
  }
}

void ParticleSystem::render()
{
  m_gpuProgram->use();

  glBindVertexArray(m_vao);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  m_gpuProgram->setUniformMatrix("projectionMat", m_renderer->getProjectionMatrix());
  m_gpuProgram->setUniformMatrix("viewMat", m_renderer->getViewMatrix());

  for (
      std::vector<Particle *>::iterator it = m_particles.begin();
      it != m_particles.end();
      it++)
  {
    const glm::vec3 &position = (*it)->position;
    const glm::vec2 &size = (*it)->size;
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size.x, size.y, 1.0f));

    if ((*it)->texture)
    {
      (*it)->texture->bind();
    }

    float opacity = (*it)->life == INFINITY ? 1.0f : (*it)->life;

    m_gpuProgram->setUniformMatrix("modelMat", modelMatrix);
    m_gpuProgram->setUniformVec4("color", (*it)->color);
    m_gpuProgram->setUniformFloat("opacity", opacity);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
  }

  glDisable(GL_BLEND);
}

void ParticleSystem::update(float timeDelta)
{
  for (int i = 0; i < m_particles.size(); i++)
    m_particles[i]->update(timeDelta);
}

Particle *ParticleSystem::emitParticle()
{
  Particle *particle = new Particle(this);

  m_particles.push_back(particle);

  return particle;
}

void ParticleSystem::releaseParticle(Particle *particle)
{
  std::vector<Particle *>::iterator it = std::find(m_particles.begin(), m_particles.end(), particle);
  if (it != m_particles.end())
  {
    delete *it;
    m_particles.erase(it);
  }
}
