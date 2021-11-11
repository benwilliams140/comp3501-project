#include "Objects/EnvironmentObject.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	EnvironmentObject::EnvironmentObject(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
	}


	EnvironmentObject::~EnvironmentObject() {
	}


	void EnvironmentObject::Update(void) {

		Rotate(GetAngM());
	}

	glm::vec3* EnvironmentObject::GetPositions() {
		return positions;
	}

	void EnvironmentObject::SetPositions(glm::vec3* listOfPos) {
		positions = listOfPos;
	}

}