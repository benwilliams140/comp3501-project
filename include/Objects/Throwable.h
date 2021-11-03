#ifndef THROWABLE_H_
#define THROWABLE_H_

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

	// Abstraction of an Throwable
	class Throwable : public SceneNode {

	public:
		// Create Throwable from given resources
		Throwable(const std::string name, const Resource* geometry, const Resource* material, glm::vec3 vel);

		// Destructor
		~Throwable();

		// Get/set attributes specific to Throwables
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		// Update geometry configuration
		void Update(void);

		bool isAlive();

	private:
		// Angular momentum of Throwable
		glm::quat angm_;
		glm::vec3 velocity;
		int lifeSpan;
		bool alive;
		float colliderBox_x;//we can change this later, doesn't have to be a float
		float colliderBox_y;//we can change this later, doesn't have to be a float
		float colliderBox_z;//we can change this later, doesn't have to be a float
	}; // class Throwable

} // namespace game

#endif // Throwable_H_