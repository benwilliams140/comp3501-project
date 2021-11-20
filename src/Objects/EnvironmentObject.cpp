#include "Objects/EnvironmentObject.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include <control/game.h>
#include <control/mathematics.h>

namespace game {
	using namespace Math;

	EnvironmentObject::EnvironmentObject(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		instanced_ = true;
	}

	EnvironmentObject::~EnvironmentObject() {
		delete[] positions_;
	}

	void EnvironmentObject::Update(void) {}

	void EnvironmentObject::InitPositions(int seed, int amount) {
		Terrain* terrain = Game::GetInstance().GetTerrain();
		positions_ = new Vector3[amount];
		instanceAmount_ = positionsSize_ = amount;

		srand(seed);
		for (int i = 0; i < amount; i++) {
			float x = randRangeFloat(-100, 100);
			float z = randRangeFloat(-100, 100);
			float y = terrain->GetHeightAt(x, z) + 1.0f;
			positions_[i] = glm::vec3(x, y, z);
		}
	}

	void EnvironmentObject::InitShaderUniform(GLuint program) {
		GLint positions_var = glGetUniformLocation(program, "positions");
		glUniform3fv(positions_var, positionsSize_, (const GLfloat*)positions_);
	}

	void EnvironmentObject::UpdateShaderUniform(GLuint program) {}

	glm::vec3* EnvironmentObject::GetPositions() {
		return positions_;
	}

	size_t EnvironmentObject::GetPositionsSize(void) const {
		return positionsSize_;
	}

	void EnvironmentObject::SetPositions(Vector3** listOfPos, size_t sizeOfPos) {
		positions_ = *listOfPos;
		positionsSize_ = sizeOfPos;
	}

}