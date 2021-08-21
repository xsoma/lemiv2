#pragma once
#include <singleton.h>
#include <vector>
#include <imgui/imgui.h>

struct BaseKey
{
	BaseKey(int c, const char* n) { this->code = c; this->name = n; };
	int code;
	const char* name;
};

class Misc
{
public:
	bool reveral_rank = true;
	bool bhop = true;
};

class AimSettings
{
public:
	bool enable = true;
	int smooth = 10;
	float fov = 5;
	bool check_team = true;
	bool only_visible = true;
	bool nerest = true;

	BaseKey aim_key = BaseKey(0x01, "LMB");

};

class PlayerSettings
{
public:
	bool esp_enable = true;
	bool esp_check_team = true;
	float visible_color[4] = {0, 1, 0, 1};
	float unvisible_color[4] = {1, 0, 0, 1};

};

class Visuals
{
public:
	bool draw_fov = false;
};

class ImFonts
{
public:
	std::vector<ImFont*> dFont;
};

class Fonts
{
public:
	ImFonts* im_fonts = new ImFonts();
	/*max 100*/
	std::vector<unsigned long> dFont;
};


class Game
{
public:
	float fov = 90;

	int override_fov = -1;
	int override_viewmodel_fov = -1;
};

class G : public Singleton<G>
{
public:
	AimSettings* aim = new AimSettings();
	PlayerSettings* player = new PlayerSettings();
	Visuals* visuals = new Visuals();
	Fonts* fonts = new Fonts();
	Game* game = new Game();
	Misc* misc = new Misc();

	float d = 2.5;
};

