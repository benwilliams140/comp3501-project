#ifndef HOVERTANKTRACK_H_
#define HOVERTANKTRACK_H_

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

	// Abstraction of an HoverTankTrack
	class HoverTankTrack : public SceneNode {

	public:
		// Create HoverTankTrack from given resources
		HoverTankTrack(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

		// Destructor
		~HoverTankTrack();

		// Update geometry configuration
		virtual void Update(void) override;

	private:
		void ActivateEffect();
		void DeactivateEffect();
		bool toggle;
	}; // class HoverTankTrack

} // namespace game

#endif // HoverTankTrack_H_