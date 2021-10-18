#include "Objects/Hovertank/hovertank_turret.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	HoverTankTurret::HoverTankTurret(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
	}


	HoverTankTurret::~HoverTankTurret() {
	}


	glm::quat HoverTankTurret::GetAngM(void) const {

		return angm_;
	}


	void HoverTankTurret::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void HoverTankTurret::Update(void) {

		Rotate(angm_);
	}

} // namespace game 