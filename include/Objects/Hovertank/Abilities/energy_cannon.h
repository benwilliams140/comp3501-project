#pragma once

#include <string>
#include <functional>
#include <utility>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Objects/Hovertank/Abilities/ability.h"
#include "Objects/Projectiles/parabolic_projectile.h"

namespace game {
	class EnergyCannon : public Ability {
	public:
		EnergyCannon(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);
		~EnergyCannon();

		// Update geometry configuration
		virtual void Update(void) override;

		// takes in the resources used to create a projectile, returns a Projectile in the outProj parameter
		virtual Projectile* UseAbility(glm::vec3 position, glm::vec3 forward) override;
	}; // class EnergyCannon
} // namespace game