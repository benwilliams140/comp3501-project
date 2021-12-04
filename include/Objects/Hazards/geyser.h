#pragma once

#include "Objects/Hazards/hazard.h"
#include "Objects/particle.h"

namespace game {
	class Geyser : public Hazard {
	public:
		Geyser(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
		~Geyser();

		virtual void Update() override;

	private:
		float cooldown_, maxCooldown_;
		float effectLength_, maxEffectLength_;
		float launchTime_;
		bool launched_;

		Particle* particle_;

		virtual void Effect() override;

	};
} // namespace game