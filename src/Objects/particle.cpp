#include "Objects/particle.h"

namespace game {
	Particle::Particle(std::string name, Resource* geom, Resource* mat, Resource* tex) : SceneNode(name, geom, mat, tex)
	{
		instanced_ = true;
		instanceAmount_ = 250;
		velMultiple_ = 1.0f;
	}

	Particle::~Particle()
	{
	}

	void Particle::Update()
	{
	}

	void Particle::SetVelocityMultiple(float multiple)
	{
		velMultiple_ = multiple;
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