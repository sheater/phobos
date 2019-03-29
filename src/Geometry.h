#pragma once

#include <glm/glm.hpp>
#include <vector>

class Geometry
{
public:
  static Geometry *createBox(const glm::vec3 &size);

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texcoords;
  std::vector<unsigned int> indices;
};
