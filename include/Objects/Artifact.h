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

namespace game {

	// Abstraction of an Artifact
	class Artifact : public SceneNode {

	public:
		// Create Artifact from given resources
		Artifact(const std::string name, const Resource* geometry, const Resource* material, const std::string artName, float val, int artifactId);

		// Destructor
		~Artifact();

		// Get/set attributes specific to Artifacts
		glm::quat GetAngM(void) const;
		void SetAngM(glm::quat angm);

		bool isFound();
		float Discover();

		std::string GetArtifactName();
		float GetValue();
		int GetId();

		// Update geometry configuration
		void Update(void);

		bool collisionDetection();

	private:
		// Angular momentum of Artifact
		glm::quat angm_;

		//doesn't have to be a square, we can change it later
		float colliderBox_x;
		float colliderBox_y;
		float colliderBox_z;

		int id;
		bool found;
		std::string artifactName; //think it would be fun to give each artifact fun, interesting unique names, of course we don't have to do this
		float value;

	}; // class Artifact

} // namespace game

#endif // Artifact_H_
