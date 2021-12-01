#include "Objects/Enemy.h"
#include "Control/game.h"
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

		return;
	}

	Math::AABBCollider Enemy::GetAwarenessBox() {
		return { GetPosition() - glm::vec3(20.0f), GetPosition() + glm::vec3(20.0f) };
	}

	Math::AABBCollider Enemy::GetCollisionBox() {
		return { GetPosition() - glm::vec3(2.5f), GetPosition() + glm::vec3(2.5f) };
	}

	bool Enemy::isStunned() {
		return stunned;
	}

	int Enemy::GetCoolDown() {
		return coolDown;
	}

	int Enemy::GetStunCoolDown() {
		return stun_coolDown;
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