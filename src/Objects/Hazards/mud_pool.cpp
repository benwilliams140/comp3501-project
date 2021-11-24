#include "Objects/Hazards/mud_pool.h"
#include "Control/game.h"

namespace game {
	MudPool::MudPool(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		effectiveness = 0.25f; // effectively a speed multiple
	}

	MudPool::~MudPool()
	{
	}

	void MudPool::Update()
	{
		Math::SphereCollider tankBox = Game::GetInstance().GetPlayer()->GetTank()->GetCollider();
		if (Math::isCollidingSphereToSphere(tankBox, GetCollider())) {
			Effect();
		}
		else {
			// no longer apply effect
			Game::GetInstance().GetPlayer()->GetTank()->SetSpeedEffectMultiple(1.0f);
		}
	}

	void MudPool::Effect()
	{
		Game::GetInstance().GetPlayer()->GetTank()->SetSpeedEffectMultiple(effectiveness);
	}
}