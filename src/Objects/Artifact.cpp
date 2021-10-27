#include "Objects/Artifact.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	Artifact::Artifact(const std::string name, const Resource* geometry, const Resource* material, const std::string artName, float val, int artifactId) : SceneNode(name, geometry, material) {
		artifactName = artifactName;
		value = val;
		id = artifactId;
		found = false;
		colliderBox_x = 10;
		colliderBox_y = 10;
		colliderBox_z = 10;
	}


	Artifact::~Artifact() {
	}


	glm::quat Artifact::GetAngM(void) const {

		return angm_;
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

	void Artifact::SetAngM(glm::quat angm) {

		angm_ = angm;
	}


	void Artifact::Update(void) {

		Rotate(angm_);
	}
	bool Artifact::isFound() {
		return found;
	}
	bool Artifact::collisionDetection() { return false; }

} // namespace game 