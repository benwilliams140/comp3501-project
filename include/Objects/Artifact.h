#ifndef ARTIFACT_H_
#define ARTIFACT_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Control/mathematics.h"

namespace game {

	// Abstraction of an Artifact
	class Artifact : public SceneNode {

	public:
		// Create Artifact from given resources
		Artifact(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture = nullptr);

		// Destructor
		~Artifact();

		// Get/set attributes specific to Artifacts
		void Setup(const std::string artName, float val, int artifactId);

		bool IsFound();
		float Discover();

		std::string GetArtifactName();
		float GetValue();
		int GetId();

		// Update geometry configuration
		void Update(void);

		// Collider
		Math::SphereCollider GetCollider(void) const;
		void EnemyCollision();
		void HovertankCollision();

	private:

		int id;
		bool found;
		std::string artifactName; //think it would be fun to give each artifact fun, interesting unique names, of course we don't have to do this
		float value;

	}; // class Artifact

} // namespace game

#endif // Artifact_H_
