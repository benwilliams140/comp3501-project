#pragma once

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Control/time.h"
#include "Control/resource_manager.h"
#include "Objects/Projectiles/projectile.h"

namespace game {
	// helper class to add projectile ability to other classes (eg. MachineGun, EnergyCannon)
	class Ability : public SceneNode {
	public:
		Ability(std::string name, const Resource* geom, const Resource* mat, const Resource* tex = nullptr);
		~Ability();

		void UpdateCooldown(); // decreases cooldown by deltaTime
		void StartCooldown(); // starts a max cooldown timer
		std::vector<Projectile*> RemoveDeadProjectiles(); // removes any expired projectiles
		std::vector<Projectile*> GetProjectiles();

		// takes in the resources used to create a projectile, returns a Projectile in the outProj parameter
		virtual Projectile* UseAbility(glm::vec3 position, glm::vec3 forward) = 0; // base ability should not be usable

		// getters
		float GetCooldown();
		float GetMaxCooldown();
		ImTextureID GetHUDTexture();

		// setters
		void SetMaxCooldown(float maxCooldown);
		void SetHUDTexture(ImTextureID hudTexture);

	protected:
		float cooldown_, maxCooldown_;
		std::vector<Projectile*> projectiles_;
		ImTextureID hudTexture_;
	}; // class Ability

} // namespace game