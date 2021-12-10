#include "Objects/ChaserEnemy.h"
#include "Control/game.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>

namespace game {

	ChaserEnemy::ChaserEnemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Enemy(name, geometry, material, texture) {
		SetSpeed(18.0f);
		meleeDamage = 10.0f;
	}


	ChaserEnemy::~ChaserEnemy() {
	}


	void ChaserEnemy::Update(void) {
		Enemy::Update();

		if (isStunned()) {
			decreaseStunCoolDown();
		}
		decreaseCoolDown();

		//check if the player is nearby
		if (detectPlayer(Game::GetInstance().GetPlayer()->GetTank())) {
			attack(Game::GetInstance().GetPlayer()->GetTank(), Game::GetInstance().GetReferenceToEnemyProjectiles());

			//have the enemy go towards the enemy
			glm::vec3 direction = glm::normalize(Game::GetInstance().GetPlayer()->GetTank()->GetPosition() - GetPosition());
			direction *= GetSpeed() * Time::GetDeltaTime();
			Translate(direction);
		}
		Translate(glm::vec3(0.0f, -5.0, 0.0f) * Time::GetDeltaTime());

		//check collision with Tank, Terrain, and other enemies
		HovertankCollision();
		TerrainCollision();
		EnemyCollision();

	}

	void ChaserEnemy::HovertankCollision() {
		//check if the enemy will collide with the tank if so, handle its movement and melee attack on tank
		if (Math::isCollidingSphereToAABB(Game::GetInstance().GetPlayer()->GetTank()->GetCollider(), GetCollisionBox())) {
			HoverTank* tank = Game::GetInstance().GetPlayer()->GetTank();
			glm::vec3 direction = glm::normalize(GetPosition() - tank->GetPosition());
			float magnitude = (tank->GetCollider().radius + 1.5f) - glm::distance(GetPosition(), tank->GetPosition());
			Translate((direction)*magnitude);

			//only attack if cooldown for attack is done
			if (GetCoolDown() <= 0) {
				Game::GetInstance().GetPlayer()->decreaseHealth(meleeDamage);
				SetCoolDown(150.0f);//set cool down for next attack
			}
		}
	}

}