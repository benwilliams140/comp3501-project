#include "Objects/Projectiles/EnergyBlast.h"
#include "Control/game.h"
#include "Objects/Enemy.h"


namespace game {

	EnergyBlast::EnergyBlast(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture) : Projectile(name, geometry, material, texture) {
		SetAlphaBlended(true);
    startTime = Time::GetDeltaTime();
		breakable_ = false;
	}

	EnergyBlast::~EnergyBlast() {
	}

	Math::SphereCollider EnergyBlast::GetCollider(void) const {
		return { GetPosition(), GetScale().x/2.0f };
	}

	void EnergyBlast::EnemyCollision() {
		//retreive all the enemies
		std::vector<Enemy*> enemies = Game::GetInstance().GetEnemies();
		for (int i = 0; i < enemies.size(); i++) {
			if (Math::isCollidingSphereToAABB(GetCollider(), enemies[i]->GetCollisionBox())) {
				//if they collided then set the enemy to the stunned state
				enemies[i]->SetStunned(true);
				enemies[i]->SetStunDown(500);
			}
		}
	}

	void EnergyBlast::Update() {
		//update postion
		SetPosition(Game::GetInstance().GetPlayer()->GetTank()->GetPosition());
		//glm::vec3 tmpval = GetScale() + glm::vec3(1.0f);
		glm::vec3 tmpval = GetScale() + glm::vec3(Time::GetDeltaTime()*3.0f);
		SetScale(tmpval);
		lifespan_ -= Time::GetDeltaTime();
		EnemyCollision();
	}

} // namespace game 