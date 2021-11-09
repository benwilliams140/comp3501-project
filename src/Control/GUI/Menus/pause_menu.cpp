#include "Control/GUI/Menus/pause_menu.h"

namespace game {
	PauseMenu::PauseMenu(GLFWwindow* window) : Menu(window) {
		
	}

	PauseMenu::~PauseMenu() {

	}

	void PauseMenu::Render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		void* ptr = glfwGetWindowUserPointer(window);
		Game* game = (Game*)ptr;

		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize;

		// demo window that shows what ImGui is capable of
		//ImGui::ShowDemoWindow((bool*) true);

		ImGui::Begin("Pause Menu", (bool*)true, flags);
		
		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2));

		// settings popup definition
		if (ImGui::BeginPopupModal("Settings", nullptr, 0)) {
			float fov = game->GetCamera()->GetFOV();
			if (ImGui::SliderFloat("FOV", &fov, 30.f, 90.f)) {
				// currently saving settings on change...
				game->GetCamera()->SetFOV(fov, windowWidth, windowHeight);
			}

			if (ImGui::Button("OK")) {
				// ...can also save settings here
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		// setup colours for elements
		ImGui::PushStyleColor(ImGuiCol_Button, BUTTON_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BUTTON_HOVERED_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, BUTTON_ACTIVE_COLOR);
		ImGui::PushStyleColor(ImGuiCol_Text, TEXT_COLOR);
		
		// resume button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - BUTTON_WIDTH / 2, windowHeight / 2 - 3 * BUTTON_HEIGHT / 2- 15));
		if (ImGui::Button("Resume", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			game->SetState(State::RUNNING);
		}

		// settings button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - BUTTON_WIDTH / 2, windowHeight / 2 - BUTTON_HEIGHT / 2 - 5));
		if (ImGui::Button("Settings", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			ImGui::OpenPopup("Settings");
		}

		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - BUTTON_WIDTH / 2, windowHeight / 2 + BUTTON_HEIGHT / 2 + 5));
		if (ImGui::Button("Exit to Menu", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			game->SetState(State::STOPPED);
		}

		ImGui::PopStyleColor(4);
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game