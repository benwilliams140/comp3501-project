#include "Control/GUI/Menus/pause_menu.h"

namespace game {
	PauseMenu::PauseMenu() : Menu() {
		
	}

	PauseMenu::~PauseMenu() {

	}

	void PauseMenu::Render(GLFWwindow* window) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		void* ptr = glfwGetWindowUserPointer(window);
		Game* game = (Game*)ptr;

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize;

		// demo window that shows what ImGui is capable of
		//ImGui::ShowDemoWindow((bool*) true);

		ImGui::Begin("Pause Menu", (bool*)true, flags);
		
		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(width / 2, height / 2));

		// settings popup definition
		if (ImGui::BeginPopupModal("Settings", nullptr, 0)) {
			float fov = game->GetCamera()->GetFOV();
			if (ImGui::SliderFloat("FOV", &fov, 30.f, 90.f)) {
				// currently saving settings on change...
				game->GetCamera()->SetFOV(fov, width, height);
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

		// quit comfirmation popup definition
		
		if (ImGui::BeginPopupModal("Quit Confirmation", nullptr, 0)) {
			ImGui::Text("Are you sure you want to quit?");
			if (ImGui::Button("OK")) {
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, BUTTON_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BUTTON_HOVERED_COLOR);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, BUTTON_ACTIVE_COLOR);
		ImGui::PushStyleColor(ImGuiCol_Text, TEXT_COLOR);
		
		// settings button definition
		ImGui::SetCursorPos(ImVec2(width / 2 - BUTTON_WIDTH / 2, height / 2 - BUTTON_HEIGHT / 2 - 5));
		if (ImGui::Button("Settings", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			ImGui::OpenPopup("Settings");
		}

		// quit button definition
		ImGui::SetCursorPos(ImVec2(width / 2 - BUTTON_WIDTH / 2, height / 2 + BUTTON_HEIGHT / 2 + 5));
		if (ImGui::Button("Quit", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			ImGui::OpenPopup("Quit Confirmation");
		}


		ImGui::PopStyleColor(4);
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game