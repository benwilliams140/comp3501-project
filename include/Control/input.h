#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <map>

namespace game {
	using Point2 = glm::vec2;

	class Input {
	public:
		static void setup(GLFWwindow* window);
		static void update(); // Resets perFrameKeys and perFrameMouseButtons, should be called before polling window events

		static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static bool getKey(std::string keyName); // Returns true if key is pressed and not released
		static bool getKeyDown(std::string keyName); // Returns true if key is pressed, resets every frames
		static bool getKeyUp(std::string keyName); // Returns true if key is released, resets every frames

		static bool getMouseButton(std::string buttonName); // Returns true if mouse button is pressed and not released
		static bool getMouseButtonDown(std::string buttonName); // Returns true if mouse button is pressed, resets every frames
		static bool getMouseButtonUp(std::string buttonName); // Returns true if mouse button is released, resets every frames

		static Point2 getMousePosition(); // Mouse position relative to window
		static Point2 getMouseDownPosition(); // Mouse position relative to window when the last left button down occured
		static Point2 getMouseScroll(); // Mouse scroll delta
		static float getAxis(std::string axis); // Horizontal or Vertical
		static float getAxisMouse(std::string axis, std::string buttonName = ""); // Horizontal or Vertical

		static float getMouseHorizontalSensitivity(void);
		static void setMouseHorizontalSensitivity(float sensitivity = 0.2f);
		static float getMouseVerticalSensitivity(void);
		static void setMouseVerticalSensitivity(float sensitivity = 0.2f);

	private:
		struct Button { bool current = false, pressed = false, released = false; };

		static std::map<std::string, Button> keys;
		static std::map<std::string, Button> mouseButtons;

		static Point2 mousePosition;
		static Point2 mouseDownPosition;
		static Point2 mousePositionDelta;
		static Point2 mouseScrollDelta;

		static float keyboardAxisSensitivity;
		static float mouseVerticalSensitivity;
		static float mouseHorizontalSensitivity;
		//static float mouseAxisSensitivity;

	};
}

// Input Key Definitions
#define INPUT_KEY_NULL ""
#define INPUT_KEY_0 "0"
#define INPUT_KEY_1 "1"
#define INPUT_KEY_2 "2"
#define INPUT_KEY_3 "3"
#define INPUT_KEY_4 "4"
#define INPUT_KEY_5 "5"
#define INPUT_KEY_6 "6"
#define INPUT_KEY_7 "7"
#define INPUT_KEY_8 "8"
#define INPUT_KEY_9 "9"
#define INPUT_KEY_A "A"
#define INPUT_KEY_B "B"
#define INPUT_KEY_C "C"
#define INPUT_KEY_D "D"
#define INPUT_KEY_E "E"
#define INPUT_KEY_F "F"
#define INPUT_KEY_G "G"
#define INPUT_KEY_H "H"
#define INPUT_KEY_I "I"
#define INPUT_KEY_J "J"
#define INPUT_KEY_K "K"
#define INPUT_KEY_L "L"
#define INPUT_KEY_M "M"
#define INPUT_KEY_N "N"
#define INPUT_KEY_O "O"
#define INPUT_KEY_P "P"
#define INPUT_KEY_Q "Q"
#define INPUT_KEY_R "R"
#define INPUT_KEY_S "S"
#define INPUT_KEY_T "T"
#define INPUT_KEY_U "U"
#define INPUT_KEY_V "V"
#define INPUT_KEY_W "W"
#define INPUT_KEY_X "X"
#define INPUT_KEY_Y "Y"
#define INPUT_KEY_Z "Z"
#define INPUT_KEY_UP "up"
#define INPUT_KEY_DOWN "down"
#define INPUT_KEY_LEFT "left"
#define INPUT_KEY_RIGHT "right"
#define INPUT_KEY_F1 "f1"
#define INPUT_KEY_F2 "f2"
#define INPUT_KEY_F3 "f3"
#define INPUT_KEY_F4 "f4"
#define INPUT_KEY_F5 "f5"
#define INPUT_KEY_F6 "f6"
#define INPUT_KEY_F7 "f7"
#define INPUT_KEY_F8 "f8"
#define INPUT_KEY_F9 "f9"
#define INPUT_KEY_F10 "f10"
#define INPUT_KEY_F11 "f11"
#define INPUT_KEY_F12 "f12"
#define INPUT_KEY_LEFT_SHIFT "left shift"
#define INPUT_KEY_LEFT_CONTROL "left control"
#define INPUT_KEY_LEFT_ALT "left alt"
#define INPUT_KEY_RIGHT_SHIFT "right shift"
#define INPUT_KEY_RIGHT_CONTROL "right control"
#define INPUT_KEY_RIGHT_ALT "right alt"
#define INPUT_KEY_ESCAPE "escape"
#define INPUT_KEY_SPACE "space"
#define INPUT_KEY_COMMA ","
#define INPUT_KEY_PERIOD "."

// Input Mouse Button Definitions
#define INPUT_MOUSE_BUTTON_1 "left"
#define INPUT_MOUSE_BUTTON_2 "right"
#define INPUT_MOUSE_BUTTON_3 "middle"

#define INPUT_MOUSE_BUTTON_LEFT INPUT_MOUSE_BUTTON_1
#define INPUT_MOUSE_BUTTON_RIGHT INPUT_MOUSE_BUTTON_2
#define INPUT_MOUSE_BUTTON_MIDDLE INPUT_MOUSE_BUTTON_3

// Input Axis Definitions
#define INPUT_AXIS_HORIZONTAL "horizontal"
#define INPUT_AXIS_VERTICAL "vertical"
