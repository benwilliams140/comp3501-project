#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Objects/Artifact.h"
#include "Objects/Projectiles/linear_projectile.h"
#include "Objects/Projectiles/parabolic_projectile.h"
#include "Objects/Hovertank/hovertank.h"
#include "Control/scene_graph.h"

namespace game {

	// Abstraction of an Player
	class Player{

	public:
		// Create Player from given resources
		Player(float hitPoints, float ePoints, HoverTank* theTank);

		// Destructor
		~Player();

		void Update();

		float GetHealth();
		float GetMaxHealth();
		void repair(float gain);
		float GetEnergy();
		float GetMaxEnergy();
		void recharge(float gain);
		bool isAlive();
		HoverTank* GetTank();
		float GetMoney();
		int GetNumArtifacts();
		float GetInjuredStartTime();
		float GetInjuredMaxTime();
		float GetStunnedStartTime();
		float GetStunnedMaxTime();

		void SetHealth(float newHealth);
		void SetMaxHealth(float newHealth);
		void decreaseHealth(float damage);
		void SetEnergy(float newEnergy);
		void SetMaxEnergy(float newEnergy);
		void energyLost(float lostEnergy);
		void AddMoney(float money);
		bool purchase(float payment);
		void Stun();

		void DiscoveredArtifact(Artifact *newArtifact);
		Artifact* GetArtifact(int id);
		void printArtifacts();


	private:
		std::vector<Artifact*> artifacts;
		float health;
		float maxHealth;
		float energy;
		float maxEnergy;
		float money;
		HoverTank* tank;

		const float maxCooldown_ = 3.0f;
		float energyRegenCooldown_, healthRegenCooldown_;

		float injuredMaxTime_ = 0.5f;
		float injuredStartTime_ = 0.0f;
		float stunnedMaxTime_ = 1.0f;
		float stunnedStartTime_ = 0.0f;
		
	}; // class Player

} // namespace game

#endif // Player_H_