#include "Objects/Hazards/mud_pool.h"
#include "Control/game.h"

namespace game {
	float MudPool::effectCooldown_;

	MudPool::MudPool(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		texOffset_ = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
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

		if (MudPool::effectCooldown_ <= 0.0f) {
			Game::GetInstance().GetPlayer()->GetTank()->SetSpeedEffectMultiple(1.0f);
		}

		MudPool::effectCooldown_ -= Time::GetDeltaTime();
	}

	void MudPool::Effect()
	{
		MudPool::effectCooldown_ = 1.0f;
		Game::GetInstance().GetPlayer()->GetTank()->SetSpeedEffectMultiple(effectiveness);
	}
}