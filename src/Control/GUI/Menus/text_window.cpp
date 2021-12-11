#include "Control/GUI/Menus/text_window.h"
#include "Control/game.h"

namespace game {
	TextWindow::TextWindow() : Menu()
	{
		stateQueue_.push_back(TextState::NOTHING); // NOTHING will always be in the stateQueue

		previouslySeen_.emplace(TextState::NOTHING, false);
		previouslySeen_.emplace(TextState::WELCOME, false);
		previouslySeen_.emplace(TextState::CONTROLS, false);
	}

	TextWindow::~TextWindow()
	{
	}

	// the TextWindow doesn't create it's own ImGui frame, uses the frame from another menu
	// this Render function should be called from within the other menu's Render functions
	void TextWindow::Render()
	{
		if (stateQueue_.front() == TextState::NOTHING) return; // don't render anything

		glfwSetInputMode(Game::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		int windowWidth, windowHeight;
		glfwGetWindowSize(Game::GetInstance().GetWindow(), &windowWidth, &windowHeight);
		ImVec2 windowSize = ImVec2(windowWidth / 2.0f, 2.0f * windowHeight / 3.0f);
		ImGui::SetNextWindowSize(windowSize);
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 4.0f, windowHeight / 6.0f));
		ImGui::SetNextItemOpen(true, ImGuiCond_Always);
		ImGui::SetNextWindowFocus();
		ImGui::SetNextWindowBgAlpha(0.95f);

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin("Text Window", (bool*)true, flags);

		switch (stateQueue_.front()) {
		case TextState::WELCOME: RenderWelcomeText(); break;
		case TextState::CONTROLS: RenderControlText(); break;
		default: break;
		}

		ImGui::SetCursorPos(ImVec2(windowSize.x - 50, windowSize.y - 25));
		if (ImGui::Button("Next")) {
			stateQueue_.erase(stateQueue_.begin());
			glfwSetInputMode(Game::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		ImGui::End();
	}
	
	void TextWindow::AddState(TextState state)
	{
		if (!previouslySeen_[state]) {
			stateQueue_.insert(stateQueue_.begin(), state);
		}
	}

	TextState TextWindow::GetState()
	{
		return stateQueue_.front();
	}
	
	void TextWindow::RenderWelcomeText()
	{
		if(!previouslySeen_[TextState::WELCOME]) previouslySeen_[TextState::WELCOME] = true;

		std::string text = "\
Hello fellow archaeologist,\n\n\
You've been tasked with finding and scanning all the ancient artifacts on planet L113.\n\n\
Beware of the native alien lifeforms as they are protecting these artifacts and will attack when approached. \
Your employer specifically stated not to kill any of these alien lifeforms, so you must only defend yourself with non-lethal weapons.\n\n\
For every artifacts scanned, your employer will pay you with credits which you can use to buy upgrades for your hovertank. \
These upgrades will be air dropped to you, so watch the sky for falling care-packages.\n\n\
Good luck!";

		ImGui::PushFont(font);
		ImGui::TextWrapped(text.c_str());
		ImGui::PopFont();
	}

	void TextWindow::RenderControlText()
	{
		if (!previouslySeen_[TextState::CONTROLS]) previouslySeen_[TextState::CONTROLS] = true;

		std::string text = "\
Controls:\n\n\
	'W'   - Move Forward\n\
	'S'   - Move Backward\n\
	'A'   - Turn Left\n\
	'D'   - Turn Right\n\
	'E'   - Scan/Interact\n\
	'LMB' - Activate Ability\n\
	'1'   - Hotbar slot 1\n\
	'2'   - Hotbar slot 2\n\
	'3'   - Hotbar slot 3\n\
	'4'   - Hotbar slot 4\n\
	'U'   - Open Upgrade Menu\n\
	'ESC' - Open Pause Menu\n\
";

		ImGui::PushFont(font);
		ImGui::TextWrapped(text.c_str());
		ImGui::PopFont();
	}
} // namespace game