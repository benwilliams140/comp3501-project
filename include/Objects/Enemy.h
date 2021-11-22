#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Control/scene_graph.h"
#include "Objects/Projectiles/Enemy_linear_projectile.h"

namespace game {

	// Abstraction of an Enemy
	class Enemy : public SceneNode {

	public:
		// Create Enemy from given resources
		Enemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~Enemy();

		// Update geometry configuration
		virtual void Update(void) override;

		glm::vec3 GetAwarenessBox();
		bool isStunned();
		bool isActive();
		int GetCoolDown();
		int GetStunCoolDown();

		void SetStunned(bool stun);
		void SetActive(bool act);
		void SetCoolDown(int time);
		void SetStunDown(int time);
		void SetAwarnessBox(glm::vec3 box);
		void decreaseStunCoolDown();
		void decreaseCoolDown();

		bool detectPlayer(SceneNode* tank);
		virtual void attack(SceneNode* tank, std::vector<Projectile*> *enemy_projectiles_);


	private:
		bool stunned; //tells if the enemy is stunned or not
		bool active; //is true when player is nearby, and it is time to attack
		glm::vec3 awarenessBox_;//a hit box if entered by the player alerts the enemy to attack
		int coolDown; //time till next attack
		int stun_coolDown; //cooldown for being stunned

	}; // class Enemy

} // namespace game

#endif // Enemy_H_ 