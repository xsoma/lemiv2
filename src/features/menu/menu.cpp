#include "menu.h"
#include <imgui/imgui.h>
#include <globals.h>
#include <iostream>

#include "custom_widgets.h"

#define BUTTONSIZE ImVec2(60, 18)
#define COLOR_EDIT_FLAGS ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs

enum class Tabs
{
	LEGIT,
	PLAYER,
	VISUALS,
	MISC,
	CONFIG
};

Tabs current_tab;

void draw_tabs()
{
	ImGui::BeginChild("###tabs", ImVec2(1024, 20));
	if (ImGui::Button("Legit bot")) current_tab = Tabs::LEGIT;
	ImGui::SameLine();
	if (ImGui::Button("Player")) current_tab = Tabs::PLAYER;
	ImGui::SameLine();
	if (ImGui::Button("Visual")) current_tab = Tabs::VISUALS;
	ImGui::SameLine();
	if (ImGui::Button("Misc")) current_tab = Tabs::MISC;
	ImGui::EndChild();
}


void draw_leigt()
{
	ImGui::BeginChild("###legit");
	ImGui::Checkbox("AIM", &G::get().aim->enable);
	ImGui::SameLine();
	ImGui::Checkbox("Only visible", &G::get().aim->only_visible);
	ImGui::Checkbox("Nerest", &G::get().aim->nerest);

	ImGui::PushItemWidth(212);
	ImGui::SliderFloat("Fov", &G::get().aim->fov, 0.0f, 360.0f, "||%.2f||");
	ImGui::SliderInt("Smooth", &G::get().aim->smooth, 0.0f, 100.0f, "||%.2f||");
	ImGui::PopItemWidth();

	ImGui::PushItemWidth(150);
	ImGui::Hotkey("Aim key", &G::get().aim->aim_key.code);
	ImGui::PopItemWidth();

	ImGui::EndChild();
}

void draw_player()
{
	ImGui::BeginChild("###player");
	ImGui::Checkbox("ESP", &G::get().player->esp_enable);
	ImGui::SameLine();
	ImGui::ColorEdit4("Visible color", G::get().player->visible_color, COLOR_EDIT_FLAGS);
	ImGui::SameLine();
	ImGui::ColorEdit4("Unvisible color", G::get().player->unvisible_color, COLOR_EDIT_FLAGS);
	ImGui::EndChild();
}

void draw_visuals()
{
	ImGui::BeginChild("###visuals");
	ImGui::Checkbox("Draw fov", &G::get().visuals->draw_fov);

	//ImGui::PushItemWidth(212);
	//ImGui::SliderInt("Override fov", &G::get().game->override_fov, 1, 250, "||%d||");
	//ImGui::SliderInt("Override viewmodel", &G::get().game->override_viewmodel_fov, 1, 250, "||%d||");
	//ImGui::PopItemWidth();

	ImGui::EndChild();
}

void draw_misc()
{
	ImGui::BeginChild("###misc");
	ImGui::Checkbox("Bhop", &G::get().misc->bhop);
	ImGui::Checkbox("Reveral ranks", &G::get().misc->reveral_rank);
	ImGui::EndChild();
}

void Menu::draw()
{
	if (!this->b_open)
		return;

	ImGui::PushFont(G::get().fonts->im_fonts->dFont[11]);

	ImGui::Begin("LemiProject", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowSize(ImVec2(1024, 600));

	draw_tabs();

	switch (current_tab)
	{
	case Tabs::LEGIT:
		draw_leigt();
		break;
	case Tabs::PLAYER:
		draw_player();
		break;
	case Tabs::VISUALS:
		draw_visuals();
		break;
	case Tabs::MISC:
		draw_misc();
		break;
	}

	ImGui::End();

	ImGui::PopFont();
}
