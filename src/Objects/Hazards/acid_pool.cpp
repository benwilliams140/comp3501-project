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
		if (cooldown_ <= 0.0f && CollisionDetection(Game::GetInstance().GetPlayer()->GetTank())) {
			Effect();
			cooldown_ = maxCooldown_;
		}
	}

	bool AcidPool::CollisionDetection(SceneNode* other)
	{
		return false;
	}

	void AcidPool::Effect()
	{
		Game::GetInstance().GetPlayer()->decreaseHealth(damage_ * effectiveness);
	}
}