#include <vector>

#include "SceneGroup.h"

class Scene: public SceneGroup {
public:
  Scene(Renderer* renderer, AssetsManager* assetsMgr);
};
