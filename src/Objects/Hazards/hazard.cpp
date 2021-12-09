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

Math::SphereCollider Hazard::GetCollider()
{
	return { GetPosition() - glm::vec3(0.0f, GetScale().y * 0.65f, 0.0f), GetScale().y };
}
} // namespace game