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
		HoverTank(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~HoverTank();

		glm::vec3 GetForward();
		glm::vec3 GetRight();
		glm::vec3 GetUp();

		// Get/set attributes specific to HoverTanks
		glm::quat GetAngM(void) const;
		float GetSpeed();
		glm::vec3 GetVelocity();
		float GetStrength();

		void SetAngM(glm::quat angm);
		void SetSpeed(float newSpeed);
		void SetVelocity(glm::vec3 newVelocity);
		void SetStrength(float newStrength);


		// Update geometry configuration
		void Update(void);

	private:
		void movementControl();
		bool collisionDetection();

		// Angular momentum of HoverTank
		glm::quat angm_;
		float speed;
		float strength;
		float colliderBox_x;//we cam change this later, doesn't have to be a float
		float colliderBox_y;//we cam change this later, doesn't have to be a float
		float colliderBox_z;//we cam change this later, doesn't have to be a float
		glm::vec3 velocity;
		glm::vec3 forward_;
	}; // class HoverTank

}
#endif