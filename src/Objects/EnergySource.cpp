#include "Objects/EnergySource.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	EnergySource::EnergySource(const std::string name, const Resource* geometry, const Resource* material, int type) : SceneNode(name, geometry, material) {
		tier = type;
		used = false;
	}


	EnergySource::~EnergySource() {
	}


	void EnergySource::Update(void) {

		Rotate(GetAngM());
	}

	float EnergySource::extractEnergy() {
		//if we already used it, then is means there isn't any energy in it
		if (used) { return 0; }

		//depending on the tier we return a set amount of energy
		if (tier == 1) {
			used = true;
			return 25.0f;
		}
		else if (tier == 2) {
			used = true;
			return 50.0f;
		}
		else {
			used = true;
			return 75.0f;
		}
	}

	bool EnergySource::isUsed() {
		return used;
	}

}