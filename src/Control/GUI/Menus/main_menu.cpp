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

		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);

		// start button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - buttonSize.x / 2, windowHeight / 2 - 3 * buttonSize.y / 2 - 5));
		if (ImGui::Button("Start", buttonSize)) {
			Game::GetInstance().SetState(State::RUNNING);
		}

		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - buttonSize.x / 2, windowHeight / 2 - buttonSize.y / 2 + 5));
		if (ImGui::Button("Quit", buttonSize)) {
			glfwSetWindowShouldClose(Game::GetInstance().GetWindow(), GL_TRUE);
		}

		ImGui::PopStyleColor(4);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game