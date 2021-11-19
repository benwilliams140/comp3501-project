#ifndef HOVERTANK_H_
#define HOVERTANK_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Objects/terrain.h"
#include "Objects/Hovertank/hovertank_turret.h"
#include "Objects/Hovertank/scanner.h"

namespace game {

	// Abstraction of an HoverTank
	class HoverTank : public SceneNode {

	public:
		// Create HoverTank from given resources
		HoverTank(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~HoverTank();

		glm::vec3 GetForward();
		glm::vec3 GetRight();
		glm::vec3 GetUp();

		// getters
		glm::vec3 GetVelocity();
		float GetStrength();
		HoverTankTurret* GetTurret();

		// setters
		void AddForce(glm::vec3 direction, float force);
		void SetStrength(float newStrength);
		void SetTurret(HoverTankTurret* turret);
		void SetScanner(Scanner* scanner);
		void SetSpeedMultiple(float multiple);

		// Update geometry configuration
		virtual void Update(void) override;

	private:
		void motionControl();
		void shootingControl();
		void terrainCollision();

		glm::vec3 velocity_;
		glm::vec3 acceleration_;
		float maxVelocity_;
		float speedMultiple_;

		float strength;
		glm::vec3 forward_;

		HoverTankTurret* turret_;
		Scanner* scanner_;
	}; // class HoverTank

}
#endif