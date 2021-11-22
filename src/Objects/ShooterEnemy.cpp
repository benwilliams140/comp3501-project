#include "Objects/ShooterEnemy.h"
#include "Control/game.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	ShooterEnemy::ShooterEnemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Enemy(name, geometry, material, texture) {
		SetAwarnessBox(glm::vec3(20.0f, 20.0f, 20.0f));
	}


	ShooterEnemy::~ShooterEnemy() {
	}


	void ShooterEnemy::Update(void) {

		if (isStunned()) {
			decreaseStunCoolDown();
		}
		decreaseCoolDown();
		if (detectPlayer(Game::GetInstance().GetPlayer()->GetTank())) {
			attack(Game::GetInstance().GetPlayer()->GetTank(), &Game::GetInstance().GetEnemyProjectiles());
		}
	}

	void ShooterEnemy::attack( SceneNode* tank, std::vector<Projectile*> *enemy_projectiles_) {
		if (!isActive()||GetCoolDown() > 0) {
			return;
		}
		static int num = 0; // used to give unique names to each projectile

		//create projectilw
		EnemyLinearProjectile* projectile = Game::GetInstance().CreateInstance<EnemyLinearProjectile>("ShooterEnemyProjectile" + std::to_string(num++), "Cube", "Simple", "RockyTexture");
		glm::vec3 vel = glm::normalize(tank->GetPosition() - GetPosition());//trajectory should be relative to player
		projectile->SetPosition(GetPosition() + 2.0f*vel);// have it spawn infront of enemy not inside
		projectile->SetVelocity(vel*10.0f);
		projectile->SetScale(glm::vec3(0.5));
		projectile->SetLifespan(3.0f);

		SetCoolDown(150);//set cool down for next shot

		enemy_projectiles_->push_back(projectile);//add it to our list of enemy projectiles

	}

}