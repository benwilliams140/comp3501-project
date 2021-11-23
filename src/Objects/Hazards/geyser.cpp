#include "Objects/Hazards/geyser.h"
#include "Control/game.h"

namespace game {
	Geyser::Geyser(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		// generate a random number between 30 and 60 for the cooldown
		maxCooldown_ = (float)rand() / (float)RAND_MAX * (60.0f - 30.0f) + 30.0f;
		cooldown_ = 0.0f;
		// boolean for whether the tank was launched in the air or not
		launched_ = false; 
		// start time of the effect
		startTime_ = 0;
		effectiveness = 10.0f;
	}

	Geyser::~Geyser() {}

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
		if (launched_) {
			// Adds a constant force to the tank for 0.5 seconds
			if ((Time::GetElapsedTime() - startTime_) <= 0.5f) {
				Game::GetInstance().GetPlayer()->GetTank()->AddForce(effectiveness * glm::vec3(0.0f, 1.0f, 0.0f), 0.8f);
			} else {
				launched_ = false;
			}
		}
	}

	void Geyser::Effect()
	{
		launched_ = true;
		startTime_ = Time::GetElapsedTime();
	}
}