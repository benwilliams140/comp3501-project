#ifndef CHASERENEMY_H
#define CHASERENEMY_H

#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include "Objects/Enemy.h"

namespace game {

	// Abstraction of an ShooterEnemy
	class ChaserEnemy : public Enemy {

	public:
		// Create ChaserEnemy from given resources
		ChaserEnemy(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~ChaserEnemy();

		virtual void Update(void) override;
		virtual void HovertankCollision() override;

	private:
		float meleeDamage;

	}; // class ChaserEnemy

} // namespace game

#endif // ChaserEnemy_H_ 