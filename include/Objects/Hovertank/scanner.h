#ifndef SCANNER_H_
#define SCANNER_H_

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

	// Abstraction of an Scanner
	class Scanner : public SceneNode {

	public:
		// Create Scanner from given resources
		Scanner(const std::string name, const Resource* geometry, const Resource* material);

		// Destructor
		~Scanner();

		// Get/set attributes specific to Scanners
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		// Update geometry configuration
		void Update(void);

	private:
		// Angular momentum of Scanner
		glm::quat angm_;
	}; // class Scanner

} // namespace game

#endif // Scanner_H_ 