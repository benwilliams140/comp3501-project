#include "Objects/Enemy.h"
#include "Control/game.h"
#include "Control/time.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace game {

	Enemy::Enemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : SceneNode(name, geometry, material, texture) {
		stunned = false;
		coolDown = 0;
		stun_coolDown = 0;
	}


	Enemy::~Enemy() {
	}


	void Enemy::Update(void) {
		texOffset_ = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, Time::GetElapsedTime() * 0.25f, 0.0f));
	}

	Math::AABBCollider Enemy::GetAwarenessBox() {
		return { GetPosition() - glm::vec3(30.0f), GetPosition() + glm::vec3(30.0f) };
	}

	Math::AABBCollider Enemy::GetCollisionBox() {
		return { GetPosition() - glm::vec3(1.0f), GetPosition() + glm::vec3(1.0f) };
	}

	void Enemy::HovertankCollision() {
		//check if the enemy will collide with the tank if so, handle its movement
		if (Math::isCollidingSphereToAABB(Game::GetInstance().GetPlayer()->GetTank()->GetCollider(), GetCollisionBox())) {
			HoverTank* tank = Game::GetInstance().GetPlayer()->GetTank();
			glm::vec3 direction = glm::normalize(GetPosition() - tank->GetPosition());
			float magnitude = (tank->GetCollider().radius + 1.5f) - glm::distance(GetPosition() , tank->GetPosition() );
			Translate((direction) *magnitude);
		}
	}

	void Enemy::EnemyCollision() {
		std::vector<Enemy*> Enemies = Game::GetInstance().GetEnemies();

		//loop through all the other enemies, and check for collisions
		for (int n = 0; n < Enemies.size(); n++) {
			//make sure we don't do a collision check with itself
			if (Enemies[n]->GetName() != GetName()) {
				if (Math::isCollidingAABBToAABB(Enemies[n]->GetCollisionBox(), GetCollisionBox())) {
					glm::vec3 direction = glm::normalize(GetPosition() - Enemies[n]->GetPosition());
					float magnitude = (1.5f + 1.5f) - glm::distance(GetPosition(), Enemies[n]->GetPosition());
					Translate((direction)*magnitude);
				}
			}
		}
	}

	void Enemy::TerrainCollision() {
		Terrain* terrain = Game::GetInstance().GetTerrain();
		glm::vec3 position = GetPosition();

		glm::vec3 hitpoint; // return value for terrain collision
		if (terrain->Collision(position, 1, hitpoint)) {
			hitpoint.y += 2.0f; // add height of tank to hitpoint
			if (position.y <= hitpoint.y) {
				Translate(glm::vec3(0, hitpoint.y - position.y, 0));
				
			}
		}
	}

	bool Enemy::isStunned() {
		return stunned;
	}

	int Enemy::GetCoolDown() {
		return coolDown;
	}

	float Enemy::GetSpeed() {
		return speed;
	}

	int Enemy::GetStunCoolDown() {
		return stun_coolDown;
	}

	void Enemy::SetSpeed(float newSpeed) {
		speed = newSpeed;
	}

	void Enemy::SetStunned(bool stun) {
		stunned = stun;
	}

	void Enemy::SetCoolDown(int time) {
		coolDown = time;
	}
	void Enemy::SetStunDown(int time) {
		stun_coolDown = time;
	}

	void Enemy::decreaseStunCoolDown() {//decrease stun cool down
		if (stun_coolDown > 0) {
			stun_coolDown = std::max(stun_coolDown - Time::GetDeltaTime(), 0.0f);
			
		}
		else {
			stunned = false;
		}
	}
	void Enemy::decreaseCoolDown() {//decrease attack cooldown
		if (coolDown > 0) {
			coolDown = stun_coolDown = std::max(coolDown - Time::GetDeltaTime(), 0.0f);

		}
	}

	bool Enemy::detectPlayer(HoverTank* tank) {
		//if the enemy is stunned then it currently can't detect the player, so just return
		if (stunned) {
			return false;
		}

		return Math::isCollidingSphereToAABB(tank->GetCollider(), GetAwarenessBox());
	}

	void Enemy::attack(SceneNode* tank, std::vector<Projectile*> *enemy_projectiles_) {
		return;
	}
}