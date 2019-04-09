#include "Geometry.h"

Geometry *Geometry::createBox(const glm::vec3 &size)
{
  Geometry *geometry = new Geometry();

  int i;
  float sx = 0.5 * size.x;
  float sy = 0.5 * size.y;
  float sz = 0.5 * size.z;

  glm::vec3 positions[] = {
      glm::vec3{sx, sy, sz},
      glm::vec3{-sx, sy, sz},
      glm::vec3{-sx, -sy, sz},
      glm::vec3{sx, -sy, sz}, // v0,v1,v2,v3 (front)
      glm::vec3{sx, sy, sz},
      glm::vec3{sx, -sy, sz},
      glm::vec3{sx, -sy, -sz},
      glm::vec3{sx, sy, -sz}, // v0,v3,v4,v5 (right)
      glm::vec3{sx, sy, sz},
      glm::vec3{sx, sy, -sz},
      glm::vec3{-sx, sy, -sz},
      glm::vec3{-sx, sy, sz}, // v0,v5,v6,v1 (top)
      glm::vec3{-sx, sy, sz},
      glm::vec3{-sx, sy, -sz},
      glm::vec3{-sx, -sy, -sz},
      glm::vec3{-sx, -sy, sz}, // v1,v6,v7,v2 (left)
      glm::vec3{-sx, -sy, -sz},
      glm::vec3{sx, -sy, -sz},
      glm::vec3{sx, -sy, sz},
      glm::vec3{-sx, -sy, sz}, // v7,v4,v3,v2 (bottom)
      glm::vec3{sx, -sy, -sz},
      glm::vec3{-sx, -sy, -sz},
      glm::vec3{-sx, sy, -sz},
      glm::vec3{sx, sy, -sz} // v4,v7,v6,v5 (back)
  };

  for (i = 0; i < 24; i++)
    geometry->positions.push_back(positions[i]);

  glm::vec3 normals[] = {
      glm::vec3{0, 0, 1},
      glm::vec3{0, 0, 1},
      glm::vec3{0, 0, 1},
      glm::vec3{0, 0, 1}, // v0,v1,v2,v3 (front)
      glm::vec3{1, 0, 0},
      glm::vec3{1, 0, 0},
      glm::vec3{1, 0, 0},
      glm::vec3{1, 0, 0}, // v0,v3,v4,v5 (right)
      glm::vec3{0, 1, 0},
      glm::vec3{0, 1, 0},
      glm::vec3{0, 1, 0},
      glm::vec3{0, 1, 0}, // v0,v5,v6,v1 (top)
      glm::vec3{-1, 0, 0},
      glm::vec3{-1, 0, 0},
      glm::vec3{-1, 0, 0},
      glm::vec3{-1, 0, 0}, // v1,v6,v7,v2 (left)
      glm::vec3{0, -1, 0},
      glm::vec3{0, -1, 0},
      glm::vec3{0, -1, 0},
      glm::vec3{0, -1, 0}, // v7,v4,v3,v2 (bottom)
      glm::vec3{0, 0, -1},
      glm::vec3{0, 0, -1},
      glm::vec3{0, 0, -1},
      glm::vec3{0, 0, -1} // v4,v7,v6,v5 (back)
  };

  for (i = 0; i < 24; i++)
    geometry->normals.push_back(normals[i]);

  glm::vec2 texcoords[] = {
      glm::vec2{1, 0},
      glm::vec2{0, 0},
      glm::vec2{0, 1},
      glm::vec2{1, 1}, // v0,v1,v2,v3 (front)
      glm::vec2{0, 0},
      glm::vec2{0, 1},
      glm::vec2{1, 1},
      glm::vec2{1, 0}, // v0,v3,v4,v5 (right)
      glm::vec2{1, 1},
      glm::vec2{1, 0},
      glm::vec2{0, 0},
      glm::vec2{0, 1}, // v0,v5,v6,v1 (top)
      glm::vec2{1, 0},
      glm::vec2{0, 0},
      glm::vec2{0, 1},
      glm::vec2{1, 1}, // v1,v6,v7,v2 (left)
      glm::vec2{0, 1},
      glm::vec2{1, 1},
      glm::vec2{1, 0},
      glm::vec2{0, 0}, // v7,v4,v3,v2 (bottom)
      glm::vec2{0, 1},
      glm::vec2{1, 1},
      glm::vec2{1, 0},
      glm::vec2{0, 0} // v4,v7,v6,v5 (back)
  };

  for (i = 0; i < 24; i++)
    geometry->texcoords.push_back(texcoords[i]);

  float indices[] = {
      0, 1, 2, 2, 3, 0,       // v0-v1-v2, v2-v3-v0 (front)
      4, 5, 6, 6, 7, 4,       // v0-v3-v4, v4-v5-v0 (right)
      8, 9, 10, 10, 11, 8,    // v0-v5-v6, v6-v1-v0 (top)
      12, 13, 14, 14, 15, 12, // v1-v6-v7, v7-v2-v1 (left)
      16, 17, 18, 18, 19, 16, // v7-v4-v3, v3-v2-v7 (bottom)
      20, 21, 22, 22, 23, 20  // v4-v7-v6, v6-v5-v4 (back)
  };

  for (i = 0; i < 36; i++)
    geometry->indices.push_back(indices[i]);

  return geometry;
}

void Geometry::transformVertices(const glm::mat4& transform)
{
  for (std::vector<glm::vec3>::iterator it = positions.begin(); it != positions.end(); it++)
  {
    // glm::vec3 vec = transform * *it;
    // it->set(vec);
    *it = glm::vec3(transform * glm::vec4(*it, 1.0f));
  }
}
