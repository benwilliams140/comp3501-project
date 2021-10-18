#ifndef HOVERTANKTURRET_H_
#define HOVERTANKTURRET_H_

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

	// Abstraction of an HoverTankTurret
	class HoverTankTurret : public SceneNode {

	public:
		// Create HoverTankTurret from given resources
		HoverTankTurret(const std::string name, const Resource* geometry, const Resource* material);

		// Destructor
		~HoverTankTurret();

		// Get/set attributes specific to HoverTankTurrets
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		// Update geometry configuration
		void Update(void);

	private:
		// Angular momentum of HoverTankTurret
		glm::quat angm_;
	}; // class HoverTankTurret

} // namespace game

#endif // HoverTankTurret_H_