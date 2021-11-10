#include "Control/GUI/Menus/main_menu.h"
#include "Control/game.h"


namespace game {
	MainMenu::MainMenu() : Menu() {
		
	}

	MainMenu::~MainMenu() {

	}

	void MainMenu::Render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int windowWidth, windowHeight;
		glfwGetWindowSize(Game::GetInstance().GetWindow(), &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize;

		ImGui::Begin("Main Menu", (bool*)true, flags);

		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2));

		ImGui::PushStyleColor(ImGuiCol_Button, BUTTON_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BUTTON_HOVERED_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, BUTTON_ACTIVE_COLOR);
		ImGui::PushStyleColor(ImGuiCol_Text, TEXT_COLOR);

		// start button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - BUTTON_WIDTH / 2, windowHeight / 2 - 3 * BUTTON_HEIGHT / 2 - 5));
		if (ImGui::Button("Start", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			Game::GetInstance().SetState(State::RUNNING);
		}

		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - BUTTON_WIDTH / 2, windowHeight / 2 - BUTTON_HEIGHT / 2 + 5));
		if (ImGui::Button("Quit", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			glfwSetWindowShouldClose(Game::GetInstance().GetWindow(), GL_TRUE);
		}

		ImGui::PopStyleColor(4);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game