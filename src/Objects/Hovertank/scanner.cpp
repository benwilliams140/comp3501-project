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


	void Scanner::Update(void) {

		Rotate(GetAngM());
	}

} // namespace game