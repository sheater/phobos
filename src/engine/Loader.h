#pragma once

#include "Asset.h"
#include "AssetsManager.h"
// class AssetsManager;

class Loader
{
public:
  Loader() : m_assetsMgr(nullptr) {}

  virtual bool isSuitableExtension(const std::string &extension) {}
  virtual Asset *loadAsset(const std::string &path) {}

protected:
  friend class AssetsManager;

  void setAssetManager(AssetsManager *assets)
  {
    m_assetsMgr = assets;
  }

  AssetsManager *m_assetsMgr;
};
