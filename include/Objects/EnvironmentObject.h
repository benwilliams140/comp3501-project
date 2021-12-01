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
		EnvironmentObject(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

		// Destructor
		~EnvironmentObject();

		// Update geometry configuration
		virtual void Update(void) override;
		void HovertankCollision();
		void ProjectileCollision();

		void InitPositions(int seed, int amount);

		glm::vec3* GetPositions();
		size_t GetPositionsSize(void) const;
		unsigned int GetInstanceGroupID(void) const;
		void SetPositions(glm::vec3** listOfPos, size_t sizeOfPos);
		void SetInstanceGroupID(unsigned int id);
		void SetColliderRadius(float radius);

	private:
		virtual void InitShaderUniform(GLuint program) override;
		virtual void UpdateShaderUniform(GLuint program) override;

		glm::vec3* positions_;
		size_t positionsSize_;
		unsigned int instGroupID_;
		float colliderRadius_;
		HoverTank* tank_;

	}; // class EnvironmentObject

} // namespace game

#endif // EnvironmentObject_H_ 