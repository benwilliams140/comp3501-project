#include "Objects/Artifact.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {
	using namespace Math;

	Artifact::Artifact(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		found = false;
	}


	Artifact::~Artifact() {
	}

	void Artifact::Setup(const std::string artName, float val, int artifactId) {
		artifactName = artifactName;
		value = val;
		id = artifactId;
	}

	int Artifact::GetId(){
		return id;
	}

	std::string Artifact::GetArtifactName() {
		return artifactName;
	}

	float Artifact::GetValue() {
		return value;
	}

	float Artifact::Discover() {
		//when discovering, and scanning the object return the value to be added to your score
		if (!found) {
			found = true;
			return value;
		}
		return 0;
	}

	void Artifact::Update(void) {

		Rotate(GetAngM());
	}

	bool Artifact::isFound() {
		return found;
	}

	SphereCollider Artifact::GetCollider(void) const {
		return {GetPosition(), 2.0f};
	}
} // namespace game 