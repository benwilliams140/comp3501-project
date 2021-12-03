#ifndef MACHINEGUN_H_
#define MACHINEGUN_H_

#include <string>
#include <stdexcept>
#include <iostream>
#include <time.h>
#include <functional>
#include <utility>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Objects/Hovertank/Abilities/ability.h"
#include "Objects/Projectiles/linear_projectile.h"

namespace game {
	// Abstraction of an MachineGun
	class MachineGun : public Ability {

	public:
		// Create MachineGun from given resources
		MachineGun(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~MachineGun();

		// Update geometry configuration
		virtual void Update(void) override;

		// takes in the resources used to create a projectile, returns a Projectile in the outProj parameter
		virtual Projectile* UseAbility(glm::vec3 position, glm::vec3 forward) override;
	}; // class MachineGun

} // namespace game

#endif // MachineGun_H_