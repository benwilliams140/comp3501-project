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

namespace game {

	// Abstraction of an HoverTank
	class HoverTank : public SceneNode {

	public:
		// Create HoverTank from given resources
		HoverTank(const std::string name, const Resource* geometry, const Resource* material, float hitPoints);

		// Destructor
		~HoverTank();

		// Get/set attributes specific to HoverTanks
		glm::quat GetAngM(void) const;
		float GetHealth();
		float GetMaxHealth();
		float GetSpeed();
		glm::vec3 GetVelocity();
		bool isAlive();
		float GetStrength();

		void SetAngM(glm::quat angm);
		void SetHealth(float newHealth);
		void SetMaxHealth(float newHealth);
		void SetSpeed(float newSpeed);
		void SetVelocity(glm::vec3 newVelocity);
		void SetStrength(float newStrength);

		void decreaseHealth(float damage);


		// Update geometry configuration
		void Update(void);

	private:
		void movementControl();
		void collisionDetection();

		// Angular momentum of HoverTank
		glm::quat angm_;
		float health;
		float maxHealth;
		float speed;
		float strength;
		float colliderBox_x;//we cam change this later, doesn't have to be a float
		float colliderBox_y;//we cam change this later, doesn't have to be a float
		float colliderBox_z;//we cam change this later, doesn't have to be a float
		glm::vec3 velocity;
		bool alive;


	}; // class HoverTank

}
#endif