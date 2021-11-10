#include "Control/GUI/menu.h"
#include "Control/path_config.h"
#include <SOIL/SOIL.h>


namespace game {
	Menu::Menu() {

	}

	Menu::~Menu() {

	}

	void Menu::AddVariable(void* var) {
		variables.push_back(var);
	}

	void Menu::HandleInput() {
		// ImGui already handles most input, this is mostly just for specialized additional features
		//		eg. Using the scroll wheel to select items in an HUD element
		// base menu object should not have any additional input (that I can think of)
	}
	ImTextureID Menu::LoadImage(std::string filename)
	{
		std::string filepath = TEXTURE_DIRECTORY + std::string("/") + filename;
		// must first load the image with SOIL and then create a texture with OpenGL
		int width, height, channels;
		unsigned char* image = SOIL_load_image(filepath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		return (ImTextureID) textureID;
	}
} // namespace game