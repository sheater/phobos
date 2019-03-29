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
  {
    delete *it;
  }

  for (std::vector<Loader *>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
  {
    delete *it;
  }
}

void AssetsManager::addLoader(Loader *loader)
{
  loader->m_assetsMgr = this;
  m_loaders.push_back(loader);
}

Asset *AssetsManager::getAsset(const std::string &path)
{
  size_t lastDot = path.find_last_of(".");
  if (lastDot == std::string::npos)
  {
    throw std::runtime_error(std::string("Path to file must contain extension: ") + path);
  }

  std::cout << "Loading " << path << std::endl;

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
  {
    std::cout << "  from cache." << std::endl;
    return result;
  }

  Loader *loader = nullptr;

  std::string extension = path.substr(lastDot + 1);
  for (std::vector<Loader *>::iterator it = m_loaders.begin(); it != m_loaders.end(); it++)
  {
    if ((*it)->isSuitableExtension(extension))
    {
      loader = *it;
      break;
    }
  }

  if (!loader)
  {
    throw std::runtime_error(std::string("Unable to find loader for: ") + path);
  }

  std::cout << "  from file." << std::endl;

  Asset* asset = loader->loadAsset(path);
  asset->m_path = path;
  m_assets.push_back(asset);
  return asset;
}
