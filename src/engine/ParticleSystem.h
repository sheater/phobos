#pragma once

#include <vector>

#include "GpuProgram.h"
#include "Renderer.h"
#include "Particle.h"

class ParticleSystem
{
public:
  ParticleSystem(Renderer *renderer);
  ~ParticleSystem();

  void render();
  void update(float timeDelta);

  Particle *emitParticle();
  void releaseParticle(Particle* particle);

private:
  void loadGpuProgram();
  void createArrayObject();

  GLuint m_vao;
  GpuProgram *m_gpuProgram;
  std::vector<Particle *> m_particles;
  Renderer *m_renderer;
};
