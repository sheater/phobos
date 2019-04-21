#pragma once

#include <vector>
#include <string>

#include "Texture.h"

#define NUM_GLYPHS_PER_WIDTH 16
#define NUM_GLYPHS_PER_HEIGHT 16
#define BASE_GLYPH_SIZE 8

class AssetsManager;

class Font
{
public:
  Font(AssetsManager* assetsMgr, const std::string& path);

  void bind();
  void renderGlyph(char c);
  glm::vec2 getGlyphSize(char c);
  // void renderText(const std::string &text);
  // unsigned int getTextWidth(const std::string &text);

private:
  Texture* m_texture;
  GLuint m_glyphs[NUM_GLYPHS_PER_WIDTH * NUM_GLYPHS_PER_HEIGHT];
};
