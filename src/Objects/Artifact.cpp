#include "Objects/Artifact.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>
#include "Control/game.h"
#include "Objects/Enemy.h"

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

		EnemyCollision();
		HovertankCollision();
	}

	bool Artifact::IsFound() {
		return found;
	}

	SphereCollider Artifact::GetCollider(void) const {
		return {GetPosition(), 2.0f};
	}

	void Artifact::EnemyCollision() {
		std::vector<Enemy*> Enemies = Game::GetInstance().GetEnemies();
		for (int n = 0; n < Enemies.size(); n++) {
			//loop through all the enemies and handle collisions
			if (Math::isCollidingSphereToAABB(GetCollider(), Enemies[n]->GetCollisionBox())) {
				Vector3 direction = glm::normalize(Enemies[n]->GetPosition() - GetPosition());
				Enemies[n]->Translate(direction);
			}
			
		}
	}

	void Artifact::HovertankCollision() {
		HoverTank* tank_ = Game::GetInstance().GetPlayer()->GetTank();
		if (Math::isCollidingSphereToSphere(tank_->GetCollider(), GetCollider())) {
			// Get direction vector from tank's position to objects positions (normalized).
			Vector3 direction = glm::normalize(tank_->GetPosition() - GetPosition());
			// Get magnitude float from ((tank's collider radius + object's collider radius) - (distance between tank and object))
			float magnitude = (tank_->GetCollider().radius + 2.0f) - glm::distance(tank_->GetPosition(), GetPosition());
			// Translate tank by direction vector times magnitude
			tank_->Translate(direction * magnitude);
		}
		
	}
} // namespace game 