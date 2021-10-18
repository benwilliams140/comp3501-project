#include "Objects/Hovertank/scanner.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	Scanner::Scanner(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
	}


	Scanner::~Scanner() {
	}


	glm::quat Scanner::GetAngM(void) const {

		return angm_;
	}


	void Scanner::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Scanner::Update(void) {

		Rotate(angm_);
	}

} // namespace game