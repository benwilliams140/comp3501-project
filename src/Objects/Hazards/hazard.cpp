#include "Objects/Hazards/hazard.h"
#include "Control/game.h"

namespace game {
Hazard::Hazard(std::string name, Resource* geometry, Resource* material, Resource* texture) : SceneNode(name, geometry, material, texture)
{
}

Hazard::~Hazard()
{
}
} // namespace game