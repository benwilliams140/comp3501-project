#include "Objects/Hazards/geyser.h"
#include "Control/game.h"

namespace game {
	Geyser::Geyser(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		// generate a random number between 30 and 60 for the cooldown
		maxCooldown_ = (float)rand() / (float)RAND_MAX * (60.0f - 30.0f) + 30.0f;
	}

	Geyser::~Geyser()
	{
	}

	void Geyser::Update()
	{
		cooldown_ -= Time::GetDeltaTime();
		if (cooldown_ <= 0.0f) {
			// should start geyser rendering here (is it happening in a shader?)

			// test if the tank is colliding
			if (CollisionDetection(Game::GetInstance().GetPlayer()->GetTank())) {
				Effect();
			}
		}
	}

	bool Geyser::CollisionDetection(SceneNode* other)
	{
		return false;
	}

	void Geyser::Effect()
	{
		HoverTank* tank = Game::GetInstance().GetPlayer()->GetTank();
		tank->SetVelocity(tank->GetVelocity() + effectiveness * glm::vec3(0.0f, 50.0f, 0.0f)); // edit this value as necessary
	}
}