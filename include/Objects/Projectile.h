#ifndef PROJECTILE_H_
#define PROJECTILE_H_

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

	// Abstraction of an Projectile
	class Projectile : public SceneNode {

	public:
		// Create Projectile from given resources
		Projectile(const std::string name, const Resource* geometry, const Resource* material,glm::vec3 vel);

		// Destructor
		~Projectile();

		// Get/set attributes specific to Projectiles
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		// Update geometry configuration
		void Update(void);

		bool isAlive();

	private:
		// Angular momentum of Projectile
		glm::quat angm_;
		glm::vec3 velocity;
		int lifeSpan;
		bool alive;
		float colliderBox_x;//we can change this later, doesn't have to be a float
		float colliderBox_y;//we can change this later, doesn't have to be a float
		float colliderBox_z;//we can change this later, doesn't have to be a float
	}; // class Projectile

} // namespace game

#endif // Projectile_H_