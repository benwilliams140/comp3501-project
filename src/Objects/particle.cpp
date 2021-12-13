#include "Objects/particle.h"
#include "Control/game.h"

namespace game {
	Particle::Particle(std::string name, Resource* geom, Resource* mat, Resource* tex) : SceneNode(name, geom, mat, tex)
	{
		instanced_ = true;
		instanceAmount_ = 250;
		velMultiple_ = 1.0f;
		SetAlphaBlended(true);
	}

	Particle::~Particle()
	{
		Game::GetInstance().RemoveInstance(this);
	}

	void Particle::Update()
	{
	}

	void Particle::Draw(Camera* camera)
	{
		// only draws particle if within set distance
		if (Math::isCollidingSphereToSphere(Game::GetInstance().GetPlayer()->GetTank()->GetCollider(), GetCollider())) {
			SceneNode::Draw(camera);
		}
	}

	float Particle::GetVelocityMultiple()
	{
		return velMultiple_;
	}

	void Particle::SetVelocityMultiple(float multiple)
	{
		velMultiple_ = multiple;
	}

	void Particle::SetInstanceAmount(int amount)
	{
		instanceAmount_ = amount;
	}

	Math::SphereCollider Particle::GetCollider()
	{
		// used to see if the particle should be drawn
		return { GetPosition(), 150.0f };
	}

	void Particle::InitShaderUniform(GLuint program)
	{
	}

	void Particle::UpdateShaderUniform(GLuint program)
	{
		GLint velMultiple_loc = glGetUniformLocation(program, "velocityMultiple");
		glUniform1f(velMultiple_loc, velMultiple_);
	}
} // namespace game