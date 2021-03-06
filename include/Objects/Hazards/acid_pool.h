#pragma once

#include "Objects/Hazards/hazard.h"

namespace game {
	class AcidPool : public Hazard {
	public:
		AcidPool(std::string name, Resource* geometry, Resource* material, Resource* texture = nullptr);
		~AcidPool();

		virtual void Update() override;

	private:
		float cooldown_;
		const float maxCooldown_ = 0.2f; // cooldown between damage effect
		const float damage_ = 5.0f;

		virtual void Effect() override;
	};
} // namespace game