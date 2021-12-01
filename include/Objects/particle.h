#pragma once

#include "Control/scene_node.h"

namespace game {
class Particle : public SceneNode {
public:
	Particle(std::string name, Resource* geom, Resource* mat, Resource* tex = nullptr);
	~Particle();

	virtual void Update() override;

	void SetVelocityMultiple(float multiple);

private:
	float velMultiple_;

	virtual void InitShaderUniform(GLuint program) override;
	virtual void UpdateShaderUniform(GLuint program) override;

}; // class Particle
} // namespace game