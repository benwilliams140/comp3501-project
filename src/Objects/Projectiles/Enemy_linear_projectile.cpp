#include "Objects/Projectiles/Enemy_linear_projectile.h"
#include "Control/game.h"
namespace game {

	EnemyLinearProjectile::EnemyLinearProjectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Projectile(name, geometry, material, texture) {
		attack_pow = 10.0f;
		breakable_ = true;
	}


	EnemyLinearProjectile::~EnemyLinearProjectile() {
	}

	void EnemyLinearProjectile::Update() {
		//update postion
		Translate(velocity_ * Time::GetDeltaTime());
		texOffset_ = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, Time::GetElapsedTime() * 0.25f, 0.0f));
		lifespan_ -= Time::GetDeltaTime();
		TankCollision();
		ArtifactCollision();
	}

	void EnemyLinearProjectile::TankCollision() {
		//check if the projectile collided with the tank
		if (Math::isCollidingSphereToSphere(GetCollider(), Game::GetInstance().GetPlayer()->GetTank()->GetCollider())) {
			//if they collided then the projectile's life span is set to 0, so it will be destroyed,
			//have the tank take damage
			lifespan_ = 0.0f;
			Game::GetInstance().GetPlayer()->decreaseHealth(attack_pow);
			if (Math::randRangeFloat(0, 1) <= 0.3333) {
				Game::GetInstance().GetPlayer()->Stun();
			}
		}

	}

} // namespace game 