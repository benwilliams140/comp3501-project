#pragma once
#ifndef ROCK_H
#define ROCK_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Objects/EnvironmentObject.h"

namespace game {

	// Abstraction of an Rock
	class Rock : public EnvironmentObject {

	public:
		// Create Rock from given resources
		Rock(const std::string name, const Resource* geometry, const Resource* material);

		// Destructor
		~Rock();

		// Update geometry configuration
		virtual void Update(void) override;


	}; // class Rock

} // namespace game

#endif // Rock_H_ 