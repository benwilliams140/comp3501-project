#include "../headers/MachineGun.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	MachineGun::MachineGun(const std::string name, const Resource *geometry, const Resource *material) : SceneNode(name, geometry, material) {
	}


	MachineGun::~MachineGun() {
	}


	glm::quat MachineGun::GetAngM(void) const {

		return angm_;
	}


	void MachineGun::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void MachineGun::Update(void) {

		Rotate(angm_);
	}

} // namespace game