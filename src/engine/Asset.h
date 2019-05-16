#pragma once

#include <string>

class Asset
{
public:
  virtual ~Asset() {}

protected:
  friend class AssetsManager;
  std::string m_path;
};
