#ifndef PARABOLIC_PROJECTILE_H_
#define PARABOLIC_PROJECTILE_H_

#include "Objects/Projectiles/projectile.h"

namespace game {

	// Abstraction of an Throwable
	class ParabolicProjectile : public Projectile {

	public:
		// Create Throwable from given resources
		ParabolicProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~ParabolicProjectile();

		// Update geometry configuration
		virtual void Update() override;
	private:
		const float gravity_ = 15.81f;
	}; // class ParabolicProjectile

} // namespace game

#endif // PARABOLIC_PROJECTILE_H_