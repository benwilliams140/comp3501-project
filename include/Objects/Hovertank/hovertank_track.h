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

		// Get/set attributes specific to HoverTankTracks
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);


		// Update geometry configuration
		void Update(void);

	private:
		void ActivateEffect();
		void DeactivateEffect();
		// Angular momentum of HoverTankTrack
		glm::quat angm_;
		bool toggle;
	}; // class HoverTankTrack

} // namespace game

#endif // HoverTankTrack_H_