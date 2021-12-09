#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <time.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Control/scene_node.h"
#include "Control/resource.h"
#include "Control/mathematics.h"


namespace game {
	class Projectile : public SceneNode {
	public:
		Projectile(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);
		~Projectile();

		// Get/set projectile properties
		virtual Math::SphereCollider GetCollider(void) const;
		void SetVelocity(glm::vec3 vel); // must call this on creation
		void SetLifespan(float lifespan); // must call this on creation
		virtual void EnemyCollision();
		void ArtifactCollision();
		bool IsAlive();

	protected:
		// projectile properties, accessable by classes that extend this
		glm::vec3 velocity_;
		float lifespan_;
	}; // class Projectile
}; // namespace game