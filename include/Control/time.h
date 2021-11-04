#pragma once

#include <GLFW/glfw3.h>

namespace game {
class Time {
public:
	static void Initialize(); // initialize time values
	static void Update(); // update time values

	static float GetDeltaTime(); // get time since last frame
	static float GetElapsedTime(); // get time since program start

private:
	static float elapsedTime_, lastTime_, deltaTime_;
}; // class Time
}; //namespace game