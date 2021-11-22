#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include "Objects/Projectiles/Enemy_linear_projectile.h"
#include "Objects/Enemy.h"

namespace game {

	// Abstraction of an ShooterEnemy
	class ShooterEnemy : public Enemy {

	public:
		// Create ShooterEnemy from given resources
		ShooterEnemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~ShooterEnemy();

		virtual void attack(SceneNode* tank, std::vector<Projectile*> *enemy_projectiles_) override;

		virtual void Update(void) override;


	}; // class ShooterEnemy

} // namespace game

#endif // ShooterEnemy_H_ 