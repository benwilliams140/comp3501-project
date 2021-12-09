#include "Control/GUI/menu.h"
#include "Control/path_config.h"
#include "Control/game.h"
#include <SOIL/SOIL.h>


namespace game {
	Menu::Menu() {
		glfwGetWindowSize(Game::GetInstance().GetWindow(), &initialWindowWidth, &initialWindowHeight);
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

	// make sure the image you are loading has an alpha channel
	ImTextureID Menu::LoadImage(std::string filename)
	{
		std::string filepath = TEXTURE_DIRECTORY + std::string("/gui/") + filename;
		GLuint textureID = SOIL_load_OGL_texture(filepath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
		if (!textureID) {
			throw(std::ios_base::failure(std::string("Error loading texture ") + std::string(filename) + std::string(": ") + std::string(SOIL_last_result())));
		}

		return (void*) (intptr_t) textureID;
	}

	ImFont* Menu::LoadFont(std::string filename, float size)
	{
		std::string filepath = FONT_DIRECTORY + std::string("/") + filename;
		return ImGui::GetIO().Fonts->AddFontFromFileTTF(filepath.c_str(), size);
	}
} // namespace game