#pragma once

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Control/time.h"
#include "Control/resource_manager.h"
#include "Objects/Projectiles/projectile.h"

namespace game {
	// helper class to add projectile ability to other classes (eg. MachineGun, EnergyCannon)
	class Ability {
	public:
		Ability(float maxCooldown);
		~Ability();

		void UpdateCooldown(); // decreases cooldown by deltaTime
		void StartCooldown(); // starts a max cooldown timer
		std::vector<Projectile*> RemoveDeadProjectiles(); // removes any expired projectiles

		// takes in the resources used to create a projectile, returns a Projectile in the outProj parameter
		virtual void UseAbility(Projectile** outProj, glm::vec3 forward, Resource* geometry, Resource* material, Resource* texture = nullptr) = 0; // base ability should not be usable

	protected:
		float cooldown_, maxCooldown_;
		std::vector<Projectile*> projectiles_;
	}; // class Ability

} // namespace game