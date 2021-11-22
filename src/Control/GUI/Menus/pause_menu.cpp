#include "Control/GUI/Menus/pause_menu.h"
#include "Control/game.h"


namespace game {
	PauseMenu::PauseMenu() : Menu() {
		
	}

	PauseMenu::~PauseMenu() {

	}

	void PauseMenu::Render() {
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

		// demo window that shows what ImGui is capable of
		//ImGui::ShowDemoWindow((bool*) true);

		ImGui::Begin("Pause Menu", (bool*)true, flags);
		
		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2));

		// quit comfirmation popup definition
		if (ImGui::BeginPopupModal("Quit Confirmation", nullptr, 0)) {
			ImGui::Text("Are you sure you want to quit?");
			if (ImGui::Button("OK")) {
				Game::GetInstance().SetState(State::STOPPED);
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		// settings popup definition
		if (ImGui::BeginPopupModal("Settings", nullptr, 0)) {
			float fov = Game::GetInstance().GetCamera()->GetFOV();
			if (ImGui::SliderFloat("FOV", &fov, 30.f, 90.f)) {
				// currently saving settings on change...
				Game::GetInstance().GetCamera()->SetFOV(fov, windowWidth, windowHeight);
			}

			if (ImGui::Button("OK")) {
				// ...can also save settings here
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			// if saving on change then the cancel button isn't necessary
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
		
		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);

		// resume button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - buttonSize.x / 2, windowHeight / 2 - 3 * buttonSize.y / 2- 15));
		if (ImGui::Button("Resume", buttonSize)) {
			Game::GetInstance().SetState(State::RUNNING);
		}

		// settings button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - buttonSize.x / 2, windowHeight / 2 - buttonSize.y / 2 - 5));
		if (ImGui::Button("Settings", buttonSize)) {
			ImGui::OpenPopup("Settings");
		}

		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowWidth / 2 - buttonSize.x / 2, windowHeight / 2 + buttonSize.y / 2 + 5));
		if (ImGui::Button("Exit to Menu", buttonSize)) {
			ImGui::OpenPopup("Quit Confirmation");
		}

		ImGui::PopStyleColor(4);
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
} // namespace game