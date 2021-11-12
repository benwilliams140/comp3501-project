#pragma once

#include "Objects/Hazards/hazard.h"

namespace game {
	class Geyser : public Hazard {
	public:
		Geyser(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
		~Geyser();

		virtual void Update() override;
		virtual bool CollisionDetection(SceneNode* other) override;

	private:
		float cooldown_, maxCooldown_;

		virtual void Effect() override;

	};
} // namespace game