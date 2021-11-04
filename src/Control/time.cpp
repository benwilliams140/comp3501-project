#include "Control/time.h"

namespace game {
	float Time::elapsedTime_, Time::lastTime_, Time::deltaTime_;

	float Time::GetDeltaTime() {
		return deltaTime_;
	}

	float Time::GetElapsedTime() {
		return elapsedTime_;
	}

	void Time::Initialize() {
		elapsedTime_ = 0.0f;
		deltaTime_ = 0.0f;
		lastTime_ = 0.0f;
	}

	void Time::Update() {
		elapsedTime_ = glfwGetTime();
		deltaTime_ = elapsedTime_ - lastTime_;
		lastTime_ = elapsedTime_;
	}
};