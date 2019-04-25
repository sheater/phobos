#include <fstream>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "GpuProgram.h"

Shader::Shader(const std::string &shaderSource, GLenum shaderType)
{
  const char *shaderData = shaderSource.data();

  m_id = glCreateShader(shaderType);
  glShaderSource(m_id, 1, &shaderData, nullptr);
  glCompileShader(m_id);

  GLint isCompiled = 0;
  glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

    char errorLog[maxLength + 1];
    glGetShaderInfoLog(m_id, maxLength, &maxLength, &errorLog[0]);

    throw std::runtime_error(std::string("Shader compilation error: ") + errorLog);
  }
}

Shader::~Shader()
{
  glDeleteShader(m_id);
}

Shader *Shader::createFromFile(const std::string &path, GLenum type)
{
  std::cout << "Loading shader " << path << std::endl;
  std::ifstream infile{path};

  if (!infile)
  {
    throw std::runtime_error("File " + path + " does not exists");
  }

  std::string data = {std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};

  return new Shader(data, type);
}

GpuProgram::GpuProgram(GLuint id) : m_id(id)
{
}

GpuProgram::~GpuProgram()
{
  glDeleteProgram(m_id);
}

void GpuProgram::use()
{
  glUseProgram(m_id);
}

void GpuProgram::setUniformMatrix(const std::string &name, const glm::mat4 &matrix)
{
  GLint location = glGetUniformLocation(m_id, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GpuProgram::setUniformVec2(const std::string &name, const glm::vec2 &vec)
{
  GLint location = glGetUniformLocation(m_id, name.c_str());
  glUniform2fv(location, 1, glm::value_ptr(vec));
}

void GpuProgram::setUniformVec3(const std::string &name, const glm::vec3 &vec)
{
  GLint location = glGetUniformLocation(m_id, name.c_str());
  glUniform3fv(location, 1, glm::value_ptr(vec));
}

void GpuProgram::setUniformVec4(const std::string &name, const glm::vec4 &vec)
{
  GLint location = glGetUniformLocation(m_id, name.c_str());
  glUniform4fv(location, 1, glm::value_ptr(vec));
}

void GpuProgram::setUniformFloat(const std::string &name, float value)
{
  GLint location = glGetUniformLocation(m_id, name.c_str());
  glUniform1f(location, value);
}

GpuProgramFactory::~GpuProgramFactory()
{
  for (std::vector<Shader *>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
  {
    delete *it;
  }
}

void GpuProgramFactory::attachShader(Shader *shader)
{
  m_shaders.push_back(shader);
}

GpuProgram *GpuProgramFactory::createProgram()
{
  GLuint id = glCreateProgram();

  for (std::vector<Shader *>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
  {
    glAttachShader(id, (*it)->m_id);
  }

  glLinkProgram(id);

  // glDetachShader(program, vertex_shader);
  // glDetachShader(program, fragment_shader);

  return new GpuProgram(id);
}
