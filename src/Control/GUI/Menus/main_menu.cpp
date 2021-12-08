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
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse;

		ImGui::Begin("Main Menu", (bool*)true, flags);

		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2));


		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);
		ImVec2 windowSize = ImVec2(windowWidth, windowHeight);

		RenderBackground(windowSize);

		ImGui::PushStyleColor(ImGuiCol_Text, titleBar_.textColor);
		RenderTitle(windowSize);
		ImGui::PopStyleColor(1);
		
		ImGui::PushStyleColor(ImGuiCol_Text, button_.textColor);
		ImGui::PushFont(button_.font);
		RenderStartButton(windowSize, buttonSize);
		RenderQuitButton(windowSize, buttonSize);
		ImGui::PopFont();
		ImGui::PopStyleColor(1);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void MainMenu::RenderStartButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// start button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 - 5));
		if (ImGui::ImageButton(button_.startImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			Game::GetInstance().SetState(State::RUNNING);
			// the most recently added state is shown first
			((TextWindow*) Game::GetInstance().GetMenu(MenuType::TEXT_WINDOW))->AddState(TextState::CONTROLS);
			((TextWindow*)Game::GetInstance().GetMenu(MenuType::TEXT_WINDOW))->AddState(TextState::WELCOME);
		}
		ImVec2 textSize = ImGui::CalcTextSize("Start");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 - textSize.y / 2 - 5));
		ImGui::Text("Start");
	}

	void MainMenu::RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 + buttonSize.y / 2 + 5));
		if (ImGui::ImageButton(button_.quitImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			glfwSetWindowShouldClose(Game::GetInstance().GetWindow(), GL_TRUE);
		}
		ImVec2 textSize = ImGui::CalcTextSize("Quit");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 + buttonSize.y - textSize.y / 2 + 5));
		ImGui::Text("Quit");
	}

	void MainMenu::RenderBackground(ImVec2 windowSize)
	{
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::Image(background_.image, windowSize);
	}

	void MainMenu::RenderTitle(ImVec2 windowSize)
	{	
		ImVec2 textSize = ImGui::CalcTextSize(titleBar_.title.c_str());
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - 5 * textSize.x / 3, 5));
		ImGui::PushFont(titleBar_.font);
		ImGui::Text(titleBar_.title.c_str());
		ImGui::PopFont();
	}
} // namespace game