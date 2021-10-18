#include "Objects/Hovertank/hovertank_track.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	HoverTankTrack::HoverTankTrack(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
		toggle = false;
	}


	HoverTankTrack::~HoverTankTrack() {
	}


	glm::quat HoverTankTrack::GetAngM(void) const {

		return angm_;
	}


	void HoverTankTrack::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void HoverTankTrack::Update(void) {

		Rotate(angm_);
	}

	void HoverTankTrack::ActivateEffect() {
		toggle = true;
	}

	void HoverTankTrack::DeactivateEffect() {
		toggle = false;
	}

} // namespace game 