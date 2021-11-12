#include "Objects/Tree.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	Tree::Tree(const std::string name, const Resource* geometry, const Resource* material) : EnvironmentObject(name, geometry, material) {
	}


	Tree::~Tree() {
	}


	void Tree::Update(void) {

		Rotate(GetAngM());
	}

}