#include "Objects/Hovertank/hovertank_track.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	HoverTankTrack::HoverTankTrack(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		toggle = false;
	}


	HoverTankTrack::~HoverTankTrack() {
	}


	void HoverTankTrack::Update(void) {
		Rotate(GetAngM());
	}

	void HoverTankTrack::ActivateEffect() {
		toggle = true;
	}

	void HoverTankTrack::DeactivateEffect() {
		toggle = false;
	}

} // namespace game 