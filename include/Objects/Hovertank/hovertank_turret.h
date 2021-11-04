#ifndef HOVERTANKTURRET_H_
#define HOVERTANKTURRET_H_

#include <string>
#include <map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Objects/Hovertank/Abilities/ability.h"
#include "Objects/Projectiles/projectile.h"

namespace game {
	// Abstraction of an HoverTankTurret
	class HoverTankTurret : public SceneNode {

	public:
		// Create HoverTankTurret from given resources
		HoverTankTurret(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~HoverTankTurret();

		// Update geometry configuration
		virtual void Update(void) override;

		void UseSelectedAbility(Projectile** outProj, glm::vec3 forward, Resource* geometry, Resource* material, Resource* texture = nullptr);
		void SelectNextAbility();
		void SelectPreviousAbility();
		bool AddAbility(Ability*);
		std::vector<Projectile*> RemoveDeadProjectiles();

		// getters
		glm::vec3 GetForward();

		// setters
		void SetForward(glm::vec3 forward);
	
	private:
		std::vector<Ability*> availableAbilities_;
		std::vector<Ability*>::iterator selectedAbility_;
		const int abilityInventorySize_ = 4;
		glm::vec3 forward_;
	}; // class HoverTankTurret

} // namespace game

#endif // HoverTankTurret_H_