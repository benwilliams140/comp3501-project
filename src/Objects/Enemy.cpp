#include "Objects/Enemy.h"
#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace game {

	Enemy::Enemy(const std::string name, const Resource* geometry, const Resource* material) : SceneNode(name, geometry, material) {
		stunned = false;
		coolDown = 0;
		stun_coolDown = 0;
		active = false;
		
	}


	Enemy::~Enemy() {
	}


	void Enemy::Update(void) {

		return;
	}

	glm::vec3 Enemy::GetAwarenessBox() {
		return awarenessBox_;
	}

	bool Enemy::isStunned() {
		return stunned;
	}

	bool Enemy::isActive() {
		return active;
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

	void Enemy::SetActive(bool act) {
		active = act;
	}

	void Enemy::SetAwarnessBox(glm::vec3 box) {
		awarenessBox_ = box;
	}

	void Enemy::SetCoolDown(int time) {
		coolDown = time;
	}
	void Enemy::SetStunDown(int time) {
		stunned = time;
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

	bool Enemy::detectPlayer(SceneNode* tank) {
		//if the enemy is stunned then it currently can't detect the player, so just return
		if (stunned) {
			active = false;
			return active;
		}

		//get the ranges of length,width, and height of both boxes
		glm::vec3 aMin = GetPosition() - awarenessBox_;
		glm::vec3 aMax = GetPosition() + awarenessBox_;
		glm::vec3 bMin = tank->GetPosition() - tank->GetCollisionBox();
		glm::vec3 bMax = tank->GetPosition() + tank->GetCollisionBox();

		//check to see if there is an intersection if yes, it means the player is nearby, and the enemy needs to be ready to attack
		active = (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
			(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
			(aMin.z <= bMax.z && aMax.z >= bMin.z);
		
		return active;
	}

	void Enemy::attack(SceneNode* tank, std::vector<Projectile*> *enemy_projectiles_) {
		return;
	}
}