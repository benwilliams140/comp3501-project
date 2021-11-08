#ifndef LINEAR_PROJECTILE_H_
#define LINEAR_PROJECTILE_H_

#include "Objects/Projectiles/projectile.h"

namespace game {

	// Abstraction of an Projectile
	class LinearProjectile : public Projectile {

	public:
		// Create Projectile from given resources
		LinearProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~LinearProjectile();

		// Update geometry configuration
		virtual void Update() override;
	}; // class Projectile

} // namespace game

#endif // Projectile_H_