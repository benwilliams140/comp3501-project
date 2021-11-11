#pragma once
#ifndef ENERGYSOURCE_H
#define ENERGYSOURCE_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"

namespace game {

	// Abstraction of an EnergySource
	class EnergySource : public SceneNode {

	public:
		// Create EnergySource from given resources
		EnergySource(const std::string name, const Resource* geometry, const Resource* material, int type);

		// Destructor
		~EnergySource();

		// Update geometry configuration
		virtual void Update(void) override;

		float extractEnergy();
		bool isUsed();

	private:
		bool used;
		int tier; //a number from 1-3 that tells us how strong of an energy source it is. 1 being low, 3 is high.


	}; // class EnergySource

} // namespace game

#endif // EnergySource_H_ 