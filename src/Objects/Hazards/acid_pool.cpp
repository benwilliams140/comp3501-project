#include "Objects/Hazards/acid_pool.h"
#include "Control/game.h"

namespace game {
	AcidPool::AcidPool(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		cooldown_ = 0.0f;
	}

	AcidPool::~AcidPool()
	{
	}

	void AcidPool::Update()
	{
		cooldown_ -= Time::GetDeltaTime();
		Math::SphereCollider tankBox = Game::GetInstance().GetPlayer()->GetTank()->GetCollider();
		if (cooldown_ <= 0.0f && Math::isCollidingSphereToAABB(tankBox, GetCollider())) {
			Effect();
			cooldown_ = maxCooldown_;
		}
	}

	void AcidPool::Effect()
	{
		Game::GetInstance().GetPlayer()->decreaseHealth(damage_ * effectiveness);
	}
}