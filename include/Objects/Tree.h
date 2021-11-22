#pragma once
#ifndef TREE_H
#define TREE_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Objects/EnvironmentObject.h"

namespace game {

	// Abstraction of an Tree
	class Tree : public EnvironmentObject {

	public:
		// Create Tree from given resources
		Tree(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

		// Destructor
		~Tree();

		// Update geometry configuration
		virtual void Update(void) override;


	}; // class Tree

} // namespace game

#endif // Tree_H_ 
