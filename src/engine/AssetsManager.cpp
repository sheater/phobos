#include <iostream>
#include <stdexcept>

#include "Loader.h"
#include "AssetsManager.h"

AssetsManager::AssetsManager(Renderer *renderer)
    : m_renderer(renderer)
{
}

AssetsManager::~AssetsManager()
{
  for (std::vector<Asset *>::iterator it = m_assets.begin(); it != m_assets.end(); it++)
    delete *it;

  for (std::vector<Loader *>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
    delete *it;
}

void AssetsManager::addLoader(Loader *loader)
{
  loader->m_assetsMgr = this;
  m_loaders.push_back(loader);
}

Loader *AssetsManager::getLoader(const std::string &path)
{
  size_t lastDot = path.find_last_of(".");
  std::string extension = path.substr(lastDot + 1);
  for (std::vector<Loader *>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
  {
    if ((*it)->isSuitableExtension(extension))
      return *it;
  }

  return nullptr;
}

Asset *AssetsManager::getAsset(const std::string &path)
{
  Asset *result = nullptr;

  for (std::vector<Asset *>::iterator it = m_assets.begin(); it != m_assets.end(); it++)
  {
    if ((*it)->m_path == path)
    {
      result = *it;
      break;
    }
  }

  if (result)
    return result;

  std::cout << "Loading " << path << std::endl;

  Loader *loader = getLoader(path);

  if (!loader)
    throw std::runtime_error(std::string("Unable to find loader for: ") + path);

  Asset *asset = loader->loadAsset(path);
  asset->m_path = path;
  m_assets.push_back(asset);
  return asset;
}
