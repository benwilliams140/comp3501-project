#include "Objects/Hazards/hazard.h"
#include "Control/game.h"

namespace game {
Hazard::Hazard(std::string name, Resource* geometry, Resource* material, Resource* texture) : SceneNode(name, geometry, material, texture)
{
}

Hazard::~Hazard()
{
}

void Hazard::SetEffectiveness(float effectiveness)
{
	this->effectiveness = effectiveness;
}

Math::AABBCollider Hazard::GetCollider()
{
	return { GetPosition() - GetScale() * 0.65f, GetPosition() + GetScale() * 0.65f };
}
} // namespace game