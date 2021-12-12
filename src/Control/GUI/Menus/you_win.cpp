#include "Control/GUI/Menus/you_win.h"
#include "Control/game.h"

namespace game {
	YouWin::YouWin() : Menu() {
	}

	YouWin::~YouWin() {

	}

	void YouWin::Render() {
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

		ImGui::Begin("You Win", (bool*)true, flags);

		// set window position for the following modals
		ImGui::SetNextWindowPos(ImVec2(windowWidth / 2, windowHeight / 2));

		ImGui::PushStyleColor(ImGuiCol_Text, button_.textColor);

		ImVec2 buttonSize = ImVec2(windowWidth * button_.widthRatio, windowHeight * button_.heightRatio);
		ImVec2 windowSize = ImVec2(windowWidth, windowHeight);

		RenderBackground(windowSize);
		RenderQuitButton(windowSize, buttonSize);

		ImGui::PopStyleColor(1);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void YouWin::RenderQuitButton(ImVec2 windowSize, ImVec2 buttonSize)
	{
		// quit button definition
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - buttonSize.x / 2, windowSize.y / 2 - buttonSize.y / 2 + 5));
		if (ImGui::ImageButton(button_.quitImage, buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0)) {
			glfwSetWindowShouldClose(Game::GetInstance().GetWindow(), GL_TRUE);
		}
		ImVec2 textSize = ImGui::CalcTextSize("Quit");
		ImGui::SetCursorPos(ImVec2(windowSize.x / 2 - textSize.x / 2, windowSize.y / 2 - textSize.y / 2 + 5));
		ImGui::Text("Quit");
	}

	void YouWin::RenderBackground(ImVec2 windowSize)
	{
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::Image(background_.image, windowSize);
	}
}