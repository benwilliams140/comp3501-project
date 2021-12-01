#include "Objects/Hazards/geyser.h"
#include "Control/game.h"

namespace game {
	Geyser::Geyser(std::string name, Resource* geometry, Resource* material, Resource* texture) : Hazard(name, geometry, material, texture)
	{
		static int id = 0;
		// generate a random number between 30 and 60 for the cooldown
		maxCooldown_ = (float)rand() / (float)RAND_MAX * (60.0f - 30.0f) + 30.0f;
		// random number between 2 and 6 for how long the effect lasts
		maxEffectLength_ = (float)rand() / (float)RAND_MAX * (6.0f - 2.0f) + 2.0f;
		cooldown_ = 0.0f;

		launched_ = false;

		// start time of the effect
		launchTime_ = 0;
		effectiveness = 1.0f;

		particle_ = Game::GetInstance().CreateInstance<Particle>("GeyserInstancedParticle" + id++, "Sphere", "GeyserParticles");
		particle_->SetScale(glm::vec3(0.2f));
	}

	Geyser::~Geyser() {}

	void Geyser::Update()
	{
		particle_->SetPosition(GetPosition() + glm::vec3(0.0f, 3.5f, 0.0f));
		cooldown_ -= Time::GetDeltaTime();
		effectLength_ -= Time::GetDeltaTime();

		if (cooldown_ <= 0.0f) {
			effectLength_ = maxEffectLength_;
			cooldown_ = maxCooldown_;
		}

		if (effectLength_ > 0.0f) {
			particle_->SetVelocityMultiple(1.0f);

			// test if the tank is colliding
			Math::SphereCollider tankBox = Game::GetInstance().GetPlayer()->GetTank()->GetCollider();
			if (Math::isCollidingSphereToSphere(tankBox, GetCollider())) {
				Effect();
			}
		}
		else {
			particle_->SetVelocityMultiple(0.05f);
		}

		if (launched_) {
			// Adds a constant force to the tank for 0.65 seconds
			if ((Time::GetElapsedTime() - launchTime_) <= 0.65f) {
				Game::GetInstance().GetPlayer()->GetTank()->AddForce(effectiveness * glm::vec3(0.0f, 1.0f, 0.0f), 3.0f);
			} else {
				launched_ = false;
			}
		}
	}

	void Geyser::Effect()
	{
		launchTime_ = Time::GetElapsedTime();
		launched_ = true;
	}
}