#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Font.h"
#include "AssetsManager.h"

Font::Font(AssetsManager *assetsMgr, const std::string &path)
{
  m_texture = static_cast<Texture *>(assetsMgr->getAsset(path));

  glm::vec2 positions[] = {
      glm::vec2{0.0f, 1.0f},
      glm::vec2{1.0f, 1.0f},
      glm::vec2{1.0f, 0.0f},
      glm::vec2{0.0f, 0.0f},
  };

  unsigned int positionsSize = sizeof(positions);

  float glyphWidth = 1.0f / NUM_GLYPHS_PER_WIDTH;
  float glyphHeight = 1.0f / NUM_GLYPHS_PER_HEIGHT;

  int ix, iy;
  for (iy = 0; iy < NUM_GLYPHS_PER_HEIGHT; iy++)
  {
    for (ix = 0; ix < NUM_GLYPHS_PER_WIDTH; ix++)
    {
      float startX = glyphWidth * ix;
      float endX = startX + glyphWidth;
      float endY = 1.0f - glyphHeight * iy;
      float startY = endY - glyphHeight;

      glm::vec2 texcoords[] = {
          glm::vec2{startX, startY},
          glm::vec2{endX, startY},
          glm::vec2{endX, endY},
          glm::vec2{startX, endY},
      };

      GLuint indices[] = {0, 1, 2, 2, 3, 0};
      GLuint vao;

      glGenVertexArrays(1, &vao);
      glBindVertexArray(vao);

      GLuint vbo, ibo;

      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      unsigned int texcoordsSize = sizeof(texcoords);
      unsigned int totalSize = positionsSize + texcoordsSize;
      glBufferData(GL_ARRAY_BUFFER, totalSize, 0, GL_STATIC_DRAW);

      // vertex positions
      glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &positions[0]);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

      // texture coords
      glBufferSubData(GL_ARRAY_BUFFER, positionsSize, texcoordsSize, &texcoords[0]);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(positionsSize));

      // indices
      glGenBuffers(1, &ibo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

      glBindVertexArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDeleteBuffers(1, &vbo);
      glDeleteBuffers(1, &ibo);

      m_glyphs[iy * NUM_GLYPHS_PER_WIDTH + ix] = vao;
    }
  }
}

void Font::bind()
{
  m_texture->bind();
}

void Font::renderGlyph(char c)
{
  glBindVertexArray(m_glyphs[int(c)]);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
}

glm::vec2 Font::getGlyphSize(char c)
{
  // NOTE: this function is for non-monospace fonts, current font is monospaced
  return glm::vec2(BASE_GLYPH_SIZE, BASE_GLYPH_SIZE);
}
