//**************************************************************************************************//
//                                             Inputs                                               //
//**************************************************************************************************//
#include "Control/input.h"

using std::string;
using std::map;

namespace game {
	map<string, Input::Button> Input::keys;
	map<string, Input::Button> Input::mouseButtons;

	Point2 Input::mousePosition;
	Point2 Input::mouseDownPosition;
	Point2 Input::mousePositionDelta;

	float Input::keyboardAxisSensitivity;
	float Input::mouseAxisSensitivity;

	bool Input::getKey(string keyName) {
		auto itr = keys.find(keyName);
		if (itr != keys.end()) { return itr->second.current; }
		else { /*Logger::log("\nInput: warning invalid key name");*/ return false; }
	}
	bool Input::getKeyDown(string keyName) {
		auto itr = keys.find(keyName);
		if (itr != keys.end()) { return itr->second.pressed; }
		else { /*Logger::log("\nInput: warning invalid key name");*/ return false; }
	}
	bool Input::getKeyUp(string keyName) {
		auto itr = keys.find(keyName);
		if (itr != keys.end()) { return itr->second.released; }
		else { /*Logger::log("\nInput: warning invalid key name");*/ return false; }
	}

	bool Input::getMouseButton(string buttonName) {
		auto itr = mouseButtons.find(buttonName);
		if (itr != mouseButtons.end()) { return itr->second.current; }
		else { /*Logger::log("\nInput: warning invalid mouse button name");*/ return false; }
	}
	bool Input::getMouseButtonDown(string buttonName) {
		auto itr = mouseButtons.find(buttonName);
		if (itr != mouseButtons.end()) { return itr->second.pressed; }
		else { /*Logger::log("\nInput: warning invalid mouse button name");*/ return false; }
	}
	bool Input::getMouseButtonUp(string buttonName) {
		auto itr = mouseButtons.find(buttonName);
		if (itr != mouseButtons.end()) { return itr->second.released; }
		else { /*Logger::log("\nInput: warning invalid mouse button name");*/ return false; }
	}

	Point2 Input::getMousePosition() { return Input::mousePosition; }
	Point2 Input::getMouseDownPosition() { return Input::mouseDownPosition; }

	void Input::setKey(std::string keyName, bool current, bool pressed, bool released) {

	}

	float Input::getAxis(string axisName) {
		float axis = 0;
		float keyDeltaTime = keyboardAxisSensitivity/* * Time::getDT()*/;
		float mouseDeltaTime = mouseAxisSensitivity/* * Time::getDT()*/;

		if (axisName == INPUT_AXIS_HORIZONTAL) {
			if (getMouseButton(INPUT_MOUSE_BUTTON_LEFT)) axis += -mousePositionDelta.x * mouseDeltaTime;
			if (getKey(INPUT_KEY_LEFT)) axis -= keyDeltaTime;
			if (getKey(INPUT_KEY_RIGHT)) axis += keyDeltaTime;
		}
		else if (axisName == INPUT_AXIS_VERTICAL) {
			if (getMouseButton(INPUT_MOUSE_BUTTON_LEFT)) axis += -mousePositionDelta.y * mouseDeltaTime;
			if (getKey(INPUT_KEY_UP)) axis += keyDeltaTime;
			if (getKey(INPUT_KEY_DOWN)) axis -= keyDeltaTime;
		}
		else {
			/*Logger::log("Input: warning invalid axis");*/
		}
		return axis;
	}

	void Input::setup(GLFWwindow* window) {
		// Set window input callbacks
		glfwSetKeyCallback(window, Input::keyCallBack);
		glfwSetCursorPosCallback(window, Input::mousePositionCallback);
		glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
		
		// Set input sensitivity variables
		keyboardAxisSensitivity = 60.0f;
		mouseAxisSensitivity = 0.2f;

		// Set input key array
		keys[INPUT_KEY_0] = {false, false, false};
		keys[INPUT_KEY_1] = {false, false, false};
		keys[INPUT_KEY_2] = {false, false, false};
		keys[INPUT_KEY_3] = {false, false, false};
		keys[INPUT_KEY_4] = {false, false, false};
		keys[INPUT_KEY_5] = {false, false, false};
		keys[INPUT_KEY_6] = {false, false, false};
		keys[INPUT_KEY_7] = {false, false, false};
		keys[INPUT_KEY_8] = {false, false, false};
		keys[INPUT_KEY_9] = {false, false, false};
		keys[INPUT_KEY_A] = {false, false, false};
		keys[INPUT_KEY_B] = {false, false, false};
		keys[INPUT_KEY_C] = {false, false, false};
		keys[INPUT_KEY_D] = {false, false, false};
		keys[INPUT_KEY_E] = {false, false, false};
		keys[INPUT_KEY_F] = {false, false, false};
		keys[INPUT_KEY_G] = {false, false, false};
		keys[INPUT_KEY_H] = {false, false, false};
		keys[INPUT_KEY_I] = {false, false, false};
		keys[INPUT_KEY_J] = {false, false, false};
		keys[INPUT_KEY_K] = {false, false, false};
		keys[INPUT_KEY_L] = {false, false, false};
		keys[INPUT_KEY_M] = {false, false, false};
		keys[INPUT_KEY_N] = {false, false, false};
		keys[INPUT_KEY_O] = {false, false, false};
		keys[INPUT_KEY_P] = {false, false, false};
		keys[INPUT_KEY_Q] = {false, false, false};
		keys[INPUT_KEY_R] = {false, false, false};
		keys[INPUT_KEY_S] = {false, false, false};
		keys[INPUT_KEY_T] = {false, false, false};
		keys[INPUT_KEY_U] = {false, false, false};
		keys[INPUT_KEY_V] = {false, false, false};
		keys[INPUT_KEY_W] = {false, false, false};
		keys[INPUT_KEY_X] = {false, false, false};
		keys[INPUT_KEY_Y] = {false, false, false};
		keys[INPUT_KEY_Z] = {false, false, false};
		keys[INPUT_KEY_UP] = {false, false, false};
		keys[INPUT_KEY_DOWN] = {false, false, false};
		keys[INPUT_KEY_LEFT] = {false, false, false};
		keys[INPUT_KEY_RIGHT] = {false, false, false};
		keys[INPUT_KEY_F1] = {false, false, false};
		keys[INPUT_KEY_F2] = {false, false, false};
		keys[INPUT_KEY_F3] = {false, false, false};
		keys[INPUT_KEY_F4] = {false, false, false};
		keys[INPUT_KEY_F5] = {false, false, false};
		keys[INPUT_KEY_F6] = {false, false, false};
		keys[INPUT_KEY_F7] = {false, false, false};
		keys[INPUT_KEY_F8] = {false, false, false};
		keys[INPUT_KEY_F9] = {false, false, false};
		keys[INPUT_KEY_F10] = {false, false, false};
		keys[INPUT_KEY_F11] = {false, false, false};
		keys[INPUT_KEY_F12] = {false, false, false};
		keys[INPUT_KEY_LEFT_SHIFT] = {false, false, false};
		keys[INPUT_KEY_LEFT_CONTROL] = {false, false, false};
		keys[INPUT_KEY_LEFT_ALT] = {false, false, false};
		keys[INPUT_KEY_RIGHT_SHIFT] = {false, false, false};
		keys[INPUT_KEY_RIGHT_CONTROL] = {false, false, false};
		keys[INPUT_KEY_RIGHT_ALT] = {false, false, false};
		keys[INPUT_KEY_ESCAPE] = {false, false, false};
		keys[INPUT_KEY_SPACE] = {false, false, false};

		// Set input mouse button array
		mouseButtons[INPUT_MOUSE_BUTTON_1] = {false, false, false};
		mouseButtons[INPUT_MOUSE_BUTTON_2] = {false, false, false};
		mouseButtons[INPUT_MOUSE_BUTTON_3] = {false, false, false};
	}

	void Input::update() {
		for (auto itr = keys.begin(); itr != keys.end(); itr++) {
			itr->second.pressed = false; itr->second.released = false;
		}
		for (auto itr = mouseButtons.begin(); itr != mouseButtons.end(); itr++) {
			itr->second.pressed = false; itr->second.released = false;
		}
	}

#define keyPress(keyName) if(!keys[keyName].current) keys[keyName].pressed = true; keys[keyName].current = true
#define keyRelease(keyName) if(keys[keyName].current) keys[keyName].released = true; keys[keyName].current = false

	void Input::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			switch (key) {
			case GLFW_KEY_0: keyPress(INPUT_KEY_0); break;
			case GLFW_KEY_1: keyPress(INPUT_KEY_1); break;
			case GLFW_KEY_2: keyPress(INPUT_KEY_2); break;
			case GLFW_KEY_3: keyPress(INPUT_KEY_3); break;
			case GLFW_KEY_4: keyPress(INPUT_KEY_4); break;
			case GLFW_KEY_5: keyPress(INPUT_KEY_5); break;
			case GLFW_KEY_6: keyPress(INPUT_KEY_6); break;
			case GLFW_KEY_7: keyPress(INPUT_KEY_7); break;
			case GLFW_KEY_8: keyPress(INPUT_KEY_8); break;
			case GLFW_KEY_9: keyPress(INPUT_KEY_9); break;
			case GLFW_KEY_A: keyPress(INPUT_KEY_A); break;
			case GLFW_KEY_B: keyPress(INPUT_KEY_B); break;
			case GLFW_KEY_C: keyPress(INPUT_KEY_C); break;
			case GLFW_KEY_D: keyPress(INPUT_KEY_D); break;
			case GLFW_KEY_E: keyPress(INPUT_KEY_E); break;
			case GLFW_KEY_F: keyPress(INPUT_KEY_F); break;
			case GLFW_KEY_G: keyPress(INPUT_KEY_G); break;
			case GLFW_KEY_H: keyPress(INPUT_KEY_H); break;
			case GLFW_KEY_I: keyPress(INPUT_KEY_I); break;
			case GLFW_KEY_J: keyPress(INPUT_KEY_J); break;
			case GLFW_KEY_K: keyPress(INPUT_KEY_K); break;
			case GLFW_KEY_L: keyPress(INPUT_KEY_L); break;
			case GLFW_KEY_M: keyPress(INPUT_KEY_M); break;
			case GLFW_KEY_N: keyPress(INPUT_KEY_N); break;
			case GLFW_KEY_O: keyPress(INPUT_KEY_O); break;
			case GLFW_KEY_P: keyPress(INPUT_KEY_P); break;
			case GLFW_KEY_Q: keyPress(INPUT_KEY_Q); break;
			case GLFW_KEY_R: keyPress(INPUT_KEY_R); break;
			case GLFW_KEY_S: keyPress(INPUT_KEY_S); break;
			case GLFW_KEY_T: keyPress(INPUT_KEY_T); break;
			case GLFW_KEY_U: keyPress(INPUT_KEY_U); break;
			case GLFW_KEY_V: keyPress(INPUT_KEY_V); break;
			case GLFW_KEY_W: keyPress(INPUT_KEY_W); break;
			case GLFW_KEY_X: keyPress(INPUT_KEY_X); break;
			case GLFW_KEY_Y: keyPress(INPUT_KEY_Y); break;
			case GLFW_KEY_Z: keyPress(INPUT_KEY_Z); break;
			case GLFW_KEY_UP:    keyPress(INPUT_KEY_UP);    break;
			case GLFW_KEY_DOWN:  keyPress(INPUT_KEY_DOWN);  break;
			case GLFW_KEY_LEFT:  keyPress(INPUT_KEY_LEFT);  break;
			case GLFW_KEY_RIGHT: keyPress(INPUT_KEY_RIGHT); break;
			case GLFW_KEY_F1:  keyPress(INPUT_KEY_F1);  break;
			case GLFW_KEY_F2:  keyPress(INPUT_KEY_F2);  break;
			case GLFW_KEY_F3:  keyPress(INPUT_KEY_F3);  break;
			case GLFW_KEY_F4:  keyPress(INPUT_KEY_F4);  break;
			case GLFW_KEY_F5:  keyPress(INPUT_KEY_F5);  break;
			case GLFW_KEY_F6:  keyPress(INPUT_KEY_F6);  break;
			case GLFW_KEY_F7:  keyPress(INPUT_KEY_F7);  break;
			case GLFW_KEY_F8:  keyPress(INPUT_KEY_F8);  break;
			case GLFW_KEY_F9:  keyPress(INPUT_KEY_F9);  break;
			case GLFW_KEY_F10: keyPress(INPUT_KEY_F10); break;
			case GLFW_KEY_F11: keyPress(INPUT_KEY_F11); break;
			case GLFW_KEY_F12: keyPress(INPUT_KEY_F12); break;
			case GLFW_KEY_LEFT_SHIFT:    keyPress(INPUT_KEY_LEFT_SHIFT);    break;
			case GLFW_KEY_LEFT_CONTROL:  keyPress(INPUT_KEY_LEFT_CONTROL);  break;
			case GLFW_KEY_LEFT_ALT:      keyPress(INPUT_KEY_LEFT_ALT);      break;
			case GLFW_KEY_RIGHT_SHIFT:   keyPress(INPUT_KEY_RIGHT_SHIFT);   break;
			case GLFW_KEY_RIGHT_CONTROL: keyPress(INPUT_KEY_RIGHT_CONTROL); break;
			case GLFW_KEY_RIGHT_ALT:     keyPress(INPUT_KEY_RIGHT_ALT);     break;
			case GLFW_KEY_ESCAPE: keyPress(INPUT_KEY_ESCAPE);  break;
			case GLFW_KEY_SPACE:  keyPress(INPUT_KEY_SPACE);   break;
			case GLFW_KEY_COMMA:  keyPress(INPUT_KEY_COMMA);   break;
			case GLFW_KEY_PERIOD: keyPress(INPUT_KEY_PERIOD);  break;
			}
		}
		else if (action == GLFW_RELEASE) {
			switch (key) {
			case GLFW_KEY_0: keyRelease(INPUT_KEY_0); break;
			case GLFW_KEY_1: keyRelease(INPUT_KEY_1); break;
			case GLFW_KEY_2: keyRelease(INPUT_KEY_2); break;
			case GLFW_KEY_3: keyRelease(INPUT_KEY_3); break;
			case GLFW_KEY_4: keyRelease(INPUT_KEY_4); break;
			case GLFW_KEY_5: keyRelease(INPUT_KEY_5); break;
			case GLFW_KEY_6: keyRelease(INPUT_KEY_6); break;
			case GLFW_KEY_7: keyRelease(INPUT_KEY_7); break;
			case GLFW_KEY_8: keyRelease(INPUT_KEY_8); break;
			case GLFW_KEY_9: keyRelease(INPUT_KEY_9); break;
			case GLFW_KEY_A: keyRelease(INPUT_KEY_A); break;
			case GLFW_KEY_B: keyRelease(INPUT_KEY_B); break;
			case GLFW_KEY_C: keyRelease(INPUT_KEY_C); break;
			case GLFW_KEY_D: keyRelease(INPUT_KEY_D); break;
			case GLFW_KEY_E: keyRelease(INPUT_KEY_E); break;
			case GLFW_KEY_F: keyRelease(INPUT_KEY_F); break;
			case GLFW_KEY_G: keyRelease(INPUT_KEY_G); break;
			case GLFW_KEY_H: keyRelease(INPUT_KEY_H); break;
			case GLFW_KEY_I: keyRelease(INPUT_KEY_I); break;
			case GLFW_KEY_J: keyRelease(INPUT_KEY_J); break;
			case GLFW_KEY_K: keyRelease(INPUT_KEY_K); break;
			case GLFW_KEY_L: keyRelease(INPUT_KEY_L); break;
			case GLFW_KEY_M: keyRelease(INPUT_KEY_M); break;
			case GLFW_KEY_N: keyRelease(INPUT_KEY_N); break;
			case GLFW_KEY_O: keyRelease(INPUT_KEY_O); break;
			case GLFW_KEY_P: keyRelease(INPUT_KEY_P); break;
			case GLFW_KEY_Q: keyRelease(INPUT_KEY_Q); break;
			case GLFW_KEY_R: keyRelease(INPUT_KEY_R); break;
			case GLFW_KEY_S: keyRelease(INPUT_KEY_S); break;
			case GLFW_KEY_T: keyRelease(INPUT_KEY_T); break;
			case GLFW_KEY_U: keyRelease(INPUT_KEY_U); break;
			case GLFW_KEY_V: keyRelease(INPUT_KEY_V); break;
			case GLFW_KEY_W: keyRelease(INPUT_KEY_W); break;
			case GLFW_KEY_X: keyRelease(INPUT_KEY_X); break;
			case GLFW_KEY_Y: keyRelease(INPUT_KEY_Y); break;
			case GLFW_KEY_Z: keyRelease(INPUT_KEY_Z); break;
			case GLFW_KEY_UP:    keyRelease(INPUT_KEY_UP);    break;
			case GLFW_KEY_DOWN:  keyRelease(INPUT_KEY_DOWN);  break;
			case GLFW_KEY_LEFT:  keyRelease(INPUT_KEY_LEFT);  break;
			case GLFW_KEY_RIGHT: keyRelease(INPUT_KEY_RIGHT); break;
			case GLFW_KEY_F1:  keyRelease(INPUT_KEY_F1);  break;
			case GLFW_KEY_F2:  keyRelease(INPUT_KEY_F2);  break;
			case GLFW_KEY_F3:  keyRelease(INPUT_KEY_F3);  break;
			case GLFW_KEY_F4:  keyRelease(INPUT_KEY_F4);  break;
			case GLFW_KEY_F5:  keyRelease(INPUT_KEY_F5);  break;
			case GLFW_KEY_F6:  keyRelease(INPUT_KEY_F6);  break;
			case GLFW_KEY_F7:  keyRelease(INPUT_KEY_F7);  break;
			case GLFW_KEY_F8:  keyRelease(INPUT_KEY_F8);  break;
			case GLFW_KEY_F9:  keyRelease(INPUT_KEY_F9);  break;
			case GLFW_KEY_F10: keyRelease(INPUT_KEY_F10); break;
			case GLFW_KEY_F11: keyRelease(INPUT_KEY_F11); break;
			case GLFW_KEY_F12: keyRelease(INPUT_KEY_F12); break;
			case GLFW_KEY_LEFT_SHIFT:    keyRelease(INPUT_KEY_LEFT_SHIFT);    break;
			case GLFW_KEY_LEFT_CONTROL:  keyRelease(INPUT_KEY_LEFT_CONTROL);  break;
			case GLFW_KEY_LEFT_ALT:      keyRelease(INPUT_KEY_LEFT_ALT);      break;
			case GLFW_KEY_RIGHT_SHIFT:   keyRelease(INPUT_KEY_RIGHT_SHIFT);   break;
			case GLFW_KEY_RIGHT_CONTROL: keyRelease(INPUT_KEY_RIGHT_CONTROL); break;
			case GLFW_KEY_RIGHT_ALT:     keyRelease(INPUT_KEY_RIGHT_ALT);     break;
			case GLFW_KEY_ESCAPE: keyRelease(INPUT_KEY_ESCAPE);  break;
			case GLFW_KEY_SPACE:  keyRelease(INPUT_KEY_SPACE);   break;
			case GLFW_KEY_COMMA:  keyRelease(INPUT_KEY_COMMA);   break;
			case GLFW_KEY_PERIOD: keyRelease(INPUT_KEY_PERIOD);  break;
			}
		}
	}

#define mouseButtonPress(keyName) if(!mouseButtons[keyName].current) mouseButtons[keyName].pressed = true; mouseButtons[keyName].current = true
#define mouseButtonRelease(keyName) if(mouseButtons[keyName].current) mouseButtons[keyName].released = true; mouseButtons[keyName].current = false

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			switch (button) {
			case GLFW_MOUSE_BUTTON_1: mouseButtonPress(INPUT_MOUSE_BUTTON_LEFT);
				double xpos, ypos; glfwGetCursorPos(window, &xpos, &ypos);
				Input::mouseDownPosition = Point2(xpos, ypos); break;
			case GLFW_MOUSE_BUTTON_2: mouseButtonPress(INPUT_MOUSE_BUTTON_RIGHT); break;
			case GLFW_MOUSE_BUTTON_3: mouseButtonPress(INPUT_MOUSE_BUTTON_MIDDLE); break;
			}
		}
		else if (action == GLFW_RELEASE) {
			switch (button) {
			case GLFW_MOUSE_BUTTON_1: mouseButtonRelease(INPUT_MOUSE_BUTTON_LEFT);
				Input::mouseDownPosition = Point2(0.0f, 0.0f); break;
			case GLFW_MOUSE_BUTTON_2: mouseButtonRelease(INPUT_MOUSE_BUTTON_RIGHT); break;
			case GLFW_MOUSE_BUTTON_3: mouseButtonRelease(INPUT_MOUSE_BUTTON_MIDDLE); break;
			}
		}
	}

	void Input::mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
		Point2 lastMousePosition = Input::mousePosition;
		Input::mousePosition = Point2(xpos, ypos);
		Input::mousePositionDelta = lastMousePosition - Input::mousePosition;
	}
}