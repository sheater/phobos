#pragma once

#include <string>

#include "Renderer.h"
#include "Asset.h"

class Loader;

class AssetsManager
{
public:
  AssetsManager(Renderer *renderer);
  ~AssetsManager();

  void addLoader(Loader *loader);

  Loader* getLoader(const std::string &path);
  Asset *getAsset(const std::string &path);

  inline Renderer *getRenderer() { return m_renderer; }

protected:
  friend class Loader;

  Renderer *m_renderer;
  std::vector<Asset *> m_assets;
  std::vector<Loader *> m_loaders;
};
