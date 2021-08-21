#include "render_tool.h"
#include <globals.h>


void RenderTool::init(IDirect3DDevice9* device)
{
	this->device = device;
}

void RenderTool::set_draw_color(const Color& color)
{
	this->color = D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b());
}

void RenderTool::draw_filled_box(int x, int y, int w, int h, const Color& color)
{
	CInterfaces::get().i_surface->set_drawing_color(color.r(), color.g(), color.b(), color.a());
	CInterfaces::get().i_surface->draw_filled_rectangle(x, y, w, h);
}

void RenderTool::draw_border_box(int x, int y, int w, int h, const Color& color, int l)
{
	draw_filled_box(x, y, w, l, color);
	draw_filled_box(x, y, l, h, color);
	draw_filled_box(x + w, y, l, h, color);
	draw_filled_box(x, y + h, w + l, l, color);
}

void RenderTool::draw_text(int x, int y, unsigned long font, const std::string& text, bool centered, Color color)
{
	const auto surface = CInterfaces::get().i_surface;
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		surface->draw_text_font(font);
		if (centered) {
			surface->get_text_size(font, temp, text_width, text_height);
			surface->draw_text_pos(x - text_width / 2, y);
		}
		else
			surface->draw_text_pos(x, y);
		surface->set_text_color(color.r(), color.g(), color.b(), color.a());
		surface->draw_render_text(temp, wcslen(temp));
	}
}

void RenderTool::draw_cricle(int x, int y, float R, int sn, Color color)
{
	const auto surface = CInterfaces::get().i_surface;

	surface->set_drawing_color(color.r(), color.g(), color.b(), color.a());
	surface->draw_outlined_circle(x, y, R, sn);
}

void RenderTool::create_font(std::vector<ULONG>& in, const char* font, int max_size, int flags)
{
	std::vector<ULONG> out;

	for (int i = 1; i <= max_size; ++i)
	{
		ULONG tmp = CInterfaces::get().i_surface->font_create();
		CInterfaces::get().i_surface->set_font_glyph(tmp, font, i, 500, 0, 0, flags);
		out.push_back(tmp);
	}

	in = out;
}

void ImRender::init()
{
	create_font_from_file(G::get().fonts->im_fonts->dFont, "C:\\Windows\\Fonts\\Calibri.ttf", 30);
}

void ImRender::render_frame()
{
}

void ImRender::create_font_from_file(std::vector<ImFont*>& in, const char* font, int max_size, const ImWchar* glyph_ranges, const ImFontConfig* font_cfg)
{
	std::vector<ImFont*> out;
	ImGuiIO& io = ImGui::GetIO();

	for (int i = 1; i <= max_size; ++i)
	{
		auto add = io.Fonts->AddFontFromFileTTF(font, i, font_cfg, glyph_ranges);
		out.push_back(add);
	}

	in.swap(out);
}
