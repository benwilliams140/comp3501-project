#pragma once
#ifndef CARE_PACKAGE_H
#define CARE_PACKAGE_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/scene_node.h"
#include "Control/mathematics.h"

namespace game {

	// Abstraction of an Rock
	class CarePackage : public SceneNode {
		enum class PackageState { FALLING, GROUNDED };

	public:
		// Create Rock from given resources
		CarePackage(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

		// Destructor
		~CarePackage();

		// Update geometry configuration
		virtual void Update(void) override;

		// Collider
		Math::SphereCollider GetCollider(void) const;

	private:
		SceneNode* parachute_;
		PackageState state_;

		float landingTime_;

	}; // class CarePackage

} // namespace game

#endif // CARE_PACKAGE_H