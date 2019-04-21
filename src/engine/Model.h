#include <string>
#include <vector>

#include "Mesh.h"
#include "Asset.h"

class Model : public Asset
{
public:
  std::vector<Mesh *> meshes;
};
