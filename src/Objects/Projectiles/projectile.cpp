#include "Objects/Projectiles/projectile.h"
#include "Control/game.h"
#include "Objects/Enemy.h"
#include "Objects/Artifact.h"

namespace game {
	Projectile::Projectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		// lifespan must be set using SetLifespan
	}

	Projectile::~Projectile() {

	}

	void Projectile::SetVelocity(glm::vec3 vel) {
		velocity_ = vel;
	}

	void Projectile::SetLifespan(float lifespan) {
		lifespan_ = lifespan; // in seconds
	}

	bool Projectile::IsAlive() {
		return lifespan_ > 0;
	}

	bool Projectile::isBreakable() {
		return breakable_;
	}

	Math::SphereCollider Projectile::GetCollider(void) const {
		return { GetPosition(), 2.5f };
	}

	void Projectile::EnemyCollision() {
		//retreive all the enemies
		std::vector<Enemy*> enemies = Game::GetInstance().GetEnemies();
		for (int i = 0; i < enemies.size(); i++) {
			if (Math::isCollidingSphereToAABB(GetCollider(), enemies[i]->GetCollisionBox())) {
				//if they collided then the projectile's life span is set to 0, so it will be destroyed,
				//and set the enemy to the stunned state
				lifespan_ = 0.0f;
				enemies[i]->SetStunned(true);
				enemies[i]->SetStunDown(150.0f);
			}
		}
	}

	void Projectile::ArtifactCollision() {
		//retreive all the Artifacts
		std::vector<Artifact*> Artifacts = Game::GetInstance().GetArtifacts();
		for (int i = 0; i < Artifacts.size(); i++) {
			if (Math::isCollidingSphereToSphere(GetCollider(), Artifacts[i]->GetCollider())) {
				//if they collided then the projectile's life span is set to 0, so it will be destroyed
				lifespan_ = 0.0f;
			}
		}
	}

	


}; // namespace game