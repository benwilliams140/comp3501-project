#pragma once
#ifndef ENVIRONMENTOBJECT_H
#define ENVIRONMENTOBJECT_H

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

	// Abstraction of an EnvironmentObject
	class EnvironmentObject : public SceneNode {

	public:
		// Create EnvironmentObject from given resources
		EnvironmentObject(const std::string name, const Resource* geometry, const Resource* material);

		// Destructor
		~EnvironmentObject();

		// Update geometry configuration
		virtual void Update(void) override;

		glm::vec3* GetPositions();
		void SetPositions(glm::vec3* listOfPos);

	private:
		glm::vec3* positions;


	}; // class EnvironmentObject

} // namespace game

#endif // EnvironmentObject_H_ 