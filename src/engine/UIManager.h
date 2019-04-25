#pragma once

#include <vector>

#include "UINode.h"
#include "Font.h"
#include "GpuProgram.h"

class Renderer;
class AssetsManager;

class UIManager
{
public:
  UIManager(Renderer *renderer, AssetsManager *asstesMgr);
  ~UIManager();

  UIManager* attachNode(UINode *node);
  UIManager* releaseNode(UINode *node);

  void render();
  void renderQuad();

  inline Renderer *getRenderer()
  {
    return m_renderer;
  }

  inline AssetsManager *getAssetsManager()
  {
    return m_assetsMgr;
  }

  UIManager* setTranslation(const glm::vec2 &translation);
  UIManager* setSize(const glm::vec2 &size);
  UIManager* setColor(const glm::vec4 &color);

  inline Font* getFont()
  {
    return m_font;
  }

private:
  void createArrayObject();

  Renderer *m_renderer;
  AssetsManager *m_assetsMgr;
  GpuProgram *m_gpuProgram;
  GLuint m_quadVao;
  Font* m_font;

  std::vector<UINode *> m_nodes;
};
