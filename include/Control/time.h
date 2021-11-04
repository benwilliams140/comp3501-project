#pragma once

#include <GLFW/glfw3.h>

namespace game {
class Time {
public:
	static float GetDeltaTime();
	static float GetElapsedTime();
	static void Initialize();
	static void Update();

private:
	static float elapsedTime_, lastTime_, deltaTime_;
}; // class Time
}; //namespace game