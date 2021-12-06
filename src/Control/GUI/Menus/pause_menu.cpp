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

		// setup colours for elements
		ImGui::PushStyleColor(ImGuiCol_Text, button_.textColor);
		
		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);
		ImVec2 windowSize = ImVec2(windowWidth, windowHeight);

		ImGui::PushFont(button_.font);
		RenderResumeButton(windowSize, buttonSize);
		RenderSettingsButton(windowSize, buttonSize);
		RenderQuitButton(windowSize, buttonSize);
		ImGui::PopFont();

		ImGui::PopStyleColor(1);
		
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void PauseMenu::RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// quit comfirmation popup definition
		ImGui::SetNextWindowSize(ImVec2(300, 75));
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

		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 + buttonSize.y / 2 + 5));
		if (ImGui::ImageButton(button_.quitImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			ImGui::OpenPopup("Quit Confirmation");
		}
		ImVec2 textSize = ImGui::CalcTextSize("Quit");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 + buttonSize.y - textSize.y / 2 + 5));
		ImGui::Text("Quit");
	}

	void PauseMenu::RenderSettingsButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// settings popup definition
		ImGui::SetNextWindowSize(ImVec2(250, 75));
		if (ImGui::BeginPopupModal("Settings", nullptr, 0)) {
			float fov = Game::GetInstance().GetCamera()->GetFOV();
			if (ImGui::SliderFloat("FOV", &fov, 30.f, 90.f)) {
				// currently saving settings on change...
				Game::GetInstance().GetCamera()->SetFOV(fov, windowSize.x, windowSize.y);
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

		// settings button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 - 5));
		if (ImGui::ImageButton(button_.settingsImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			ImGui::OpenPopup("Settings");
		}
		ImVec2 textSize = ImGui::CalcTextSize("Settings");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 - textSize.y / 2 - 5));
		ImGui::Text("Settings");
	}

	void PauseMenu::RenderResumeButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// resume button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - 3 * buttonSize.y / 2 - 15));
		if (ImGui::ImageButton(button_.resumeImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			Game::GetInstance().SetState(State::RUNNING);
		}
		ImVec2 textSize = ImGui::CalcTextSize("Resume");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 - buttonSize.y - textSize.y / 2 - 15));
		ImGui::Text("Resume");
	}
} // namespace game