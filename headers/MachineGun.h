#ifndef MACHINEGUN_H_
#define MACHINEGUN_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "resource.h"
#include "scene_node.h"

namespace game {

	// Abstraction of an MachineGun
	class MachineGun : public SceneNode {

	public:
		// Create MachineGun from given resources
		MachineGun(const std::string name, const Resource *geometry, const Resource *material);

		// Destructor
		~MachineGun();

		// Get/set attributes specific to MachineGuns
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		// Update geometry configuration
		void Update(void);

	private:
		// Angular momentum of MachineGun
		glm::quat angm_;
	}; // class MachineGun

} // namespace game

#endif // MachineGun_H_
