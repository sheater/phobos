#pragma once

#include <OpenGL/gl.h>
#include <vector>
#include <string>
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

  void setUniformMatrix(const std::string &name, const glm::mat4 &matrix);
  void setUniformVec2(const std::string &name, const glm::vec2 &vec);
  void setUniformVec3(const std::string &name, const glm::vec3 &vec);
  void setUniformVec4(const std::string &name, const glm::vec4 &vec);
  void setUniformFloat(const std::string &name, float value);

private:
  GpuProgram(GLuint id);

  void use();

  friend class GpuProgramFactory;
  friend class Renderer;

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
