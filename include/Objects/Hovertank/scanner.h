#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>

#include "Control/resource.h"
#include "Control/scene_node.h"
#include "Objects/Artifact.h"

namespace game {

	// Abstraction of an Scanner
	class Scanner : public SceneNode {

	public:
		// Create Scanner from given resources
		Scanner(const std::string name, const Resource* geometry, const Resource* material, const Resource* texture);

		// Destructor
		~Scanner();

		// Update geometry configuration
		virtual void Update(void) override;

		bool IsScanning(void) const;
		glm::vec3 GetScanPoint(void) const;

	private:
		SceneNode* scanCone_;
		Artifact* artifact_;
		bool scanning_;
		float scanStartTime_;

	}; // class Scanner

} // namespace game

#endif // Scanner_H_ 