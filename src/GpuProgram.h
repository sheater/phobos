#pragma once

#include <OpenGL/gl.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
  Shader(const std::string &shaderSource, GLenum shaderType);
  ~Shader();

  static Shader *createFromFile(const std::string &path, GLenum type);

private:
  friend class GpuProgram;
  friend class GpuProgramFactory;

  GLuint m_id;
};

class GpuProgram
{
public:
  ~GpuProgram();

  void use();

  void setUniformMatrix(const std::string &name, const glm::mat4 &matrix);
  void setUniformVec3(const std::string &name, const glm::vec3 &vec);
  void setUniformVec4(const std::string &name, const glm::vec4 &vec);

private:
  GpuProgram(GLuint id);

  friend class GpuProgramFactory;

  GLuint m_id;
};

class GpuProgramFactory
{
public:
  ~GpuProgramFactory();

  void attachShader(Shader *shader);

  GpuProgram *createProgram();

private:
  std::vector<Shader *> m_shaders;
};
