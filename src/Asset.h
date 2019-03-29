#pragma once

#include <string>

class Asset
{
protected:
  friend class AssetsManager;
  std::string m_path;
};
