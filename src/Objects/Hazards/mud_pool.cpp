#include "Objects/Hazards/mud_pool.h"
#include "Control/game.h"

namespace game {
	MudPool::MudPool(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
	}

	MudPool::~MudPool()
	{
	}

	void MudPool::Update()
	{
		if (CollisionDetection(Game::GetInstance().GetPlayer()->GetTank())) {
			Effect();
		}
		else {
			Game::GetInstance().GetPlayer()->GetTank()->SetSpeedMultiple(1.0f);
		}
	}

	bool MudPool::CollisionDetection(SceneNode* other)
	{
		return false;
	}

	void MudPool::Effect()
	{
		Game::GetInstance().GetPlayer()->GetTank()->SetSpeedMultiple(0.25f);
	}
}