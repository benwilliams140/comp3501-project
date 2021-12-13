#pragma once

#include "Control/scene_node.h"
#include "Control/mathematics.h"

namespace game {
class Particle : public SceneNode {
public:
	Particle(std::string name, Resource* geom, Resource* mat, Resource* tex = nullptr);
	~Particle();

	virtual void Update() override;
	virtual void Draw(Camera* camera) override;

	float GetVelocityMultiple();

	void SetVelocityMultiple(float multiple);
	void SetInstanceAmount(int amount); // set the instanceAmount value in scene_node

	Math::SphereCollider GetCollider();

private:
	float velMultiple_;

	virtual void InitShaderUniform(GLuint program) override;
	virtual void UpdateShaderUniform(GLuint program) override;

}; // class Particle
} // namespace game