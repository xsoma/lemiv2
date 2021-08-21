#pragma once
#include <math/q_angle.h>
#include <math/vector2d.h>
#include <game_sdk/classes/color.h>

typedef ULONG HFont;
typedef unsigned int VPANEL;


static const wchar_t* get_wc_t(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

struct IntRect {
    int x0;
    int y0;
    int w;
    int h;
};

struct vertex_t {
    vertex_t() {}
    vertex_t(const Math::CVector2D& pos, const Math::CVector2D& coord = Math::CVector2D(0, 0)) {
        m_Position = pos;
        m_TexCoord = coord;
    }
    void init(const Math::CVector2D& pos, const Math::CVector2D& coord = Math::CVector2D(0, 0)) {
        m_Position = pos;
        m_TexCoord = coord;
    }

    Math::CVector2D m_Position;
    Math::CVector2D m_TexCoord;
};

enum class FontFeature {
    FONT_FEATURE_ANTIALIASED_FONTS = 1,
    FONT_FEATURE_DROPSHADOW_FONTS = 2,
    FONT_FEATURE_OUTLINE_FONTS = 6,
};

enum class FontDrawType {
    FONT_DRAW_DEFAULT = 0,
    FONT_DRAW_NONADDITIVE,
    FONT_DRAW_ADDITIVE,
    FONT_DRAW_TYPE_COUNT = 2,
};

enum class FontFlags {
    FONTFLAG_NONE,
    FONTFLAG_ITALIC = 0x001,
    FONTFLAG_UNDERLINE = 0x002,
    FONTFLAG_STRIKEOUT = 0x004,
    FONTFLAG_SYMBOL = 0x008,
    FONTFLAG_ANTIALIAS = 0x010,
    FONTFLAG_GAUSSIANBLUR = 0x020,
    FONTFLAG_ROTARY = 0x040,
    FONTFLAG_DROPSHADOW = 0x080,
    FONTFLAG_ADDITIVE = 0x100,
    FONTFLAG_OUTLINE = 0x200,
    FONTFLAG_CUSTOM = 0x400,
    FONTFLAG_BITMAP = 0x800,
};

#ifdef CreateFont
#undef CreateFont
#endif


class ISurface
{
public:
	void set_drawing_color(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[15](this, r, g, b, a);
	}

	void play_sound(const char* sound_path) {
		using original_fn = void(__thiscall*)(ISurface*, const char*);
		return (*(original_fn**)this)[82](this, sound_path);
	}

	void set_text_color(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[25](this, r, g, b, a);
	}

	void draw_polygon(int n, vertex_t* vertice, bool clip_vertices = true) {
		using original_fn = void(__thiscall*)(ISurface*, int, vertex_t*, bool);
		return (*(original_fn**)this)[106](this, n, vertice, clip_vertices);
	}
	void draw_filled_rectangle(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[16](this, x, y, x + w, y + h);
	}
	void set_texture(int id) {
		using original_fn = void(__thiscall*)(ISurface*, int);
		return (*(original_fn**)this)[38](this, id);
	}
	inline void draw_textured_rectangle(int x, int y, int w, int h) {
		typedef void(__thiscall* original_fn)(void*, int, int, int, int);
		return (*(original_fn**)this)[41](this, x, y, w, h);
	}
	void set_texture_rgba(int id, const unsigned char* rgba, int wide, int tall) {
		using original_fn = void(__thiscall*)(ISurface*, int, const unsigned char*, int, int);
		return (*(original_fn**)this)[37](this, id, rgba, wide, tall);
	}
	int create_new_texture_id(bool procedural = false) {
		using original_fn = int(__thiscall*)(ISurface*, bool);
		return (*(original_fn**)this)[43](this, procedural);
	}
	void draw_outlined_rect(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[18](this, x, y, x + w, y + h);
	}
	void draw_line(int x1, int y1, int x2, int y2) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[19](this, x1, y1, x2, y2);
	}
	void draw_text_font(unsigned long font) {
		using original_fn = void(__thiscall*)(ISurface*, unsigned long);
		return (*(original_fn**)this)[23](this, font);
	}
	void draw_text_pos(int x, int y) {
		using original_fn = void(__thiscall*)(ISurface*, int, int);
		return (*(original_fn**)this)[26](this, x, y);
	}
	void draw_render_text(const wchar_t* text, int textLen) {
		using original_fn = void(__thiscall*)(ISurface*, const wchar_t*, int, int);
		return (*(original_fn**)this)[28](this, text, textLen, 0);
	}
	unsigned long font_create() {
		using original_fn = unsigned int(__thiscall*)(ISurface*);
		return (*(original_fn**)this)[71](this);
	}
	void set_font_glyph(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) {
		using original_fn = void(__thiscall*)(ISurface*, unsigned long, const char*, int, int, int, int, int, int, int);
		return (*(original_fn**)this)[72](this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall) {
		using original_fn = void(__thiscall*)(ISurface*, unsigned long, const wchar_t*, int&, int&);
		return (*(original_fn**)this)[79](this, font, text, wide, tall);
	}
	void unlock_cursor() {
		using original_fn = void(__thiscall*)(ISurface*);
		return (*(original_fn**)this)[66](this);
	}

	void set_clip_rect(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[147](this, x, y, w, h);
	}

	void draw_filled_rect_fade(int x, int y, int w, int h, unsigned int alpha1, unsigned int alpha2, bool is_horizontal) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int, unsigned int, unsigned int, bool);
		return (*(original_fn**)this)[123](this, x, y, w, h, alpha1, alpha2, is_horizontal);
	}

	void draw_colored_text(unsigned long font, int x, int y, int red, int green, int blue, int alpha, const char* text) {
		using original_fn = void(__thiscall*)(ISurface*, unsigned long, int, int, int, int, int, int, const char*);
		return (*(original_fn**)this)[163](this, font, x, y, red, green, blue, alpha, text);
	}

	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(ISurface*, int&, int&);
		return (*(original_fn**)this)[44](this, std::ref(width), std::ref(height));  //width, height
	}

	void draw_textured_polygon(int vertex_count, vertex_t* vertex, bool clip_vertices = true) {
		using original_fn = void(__thiscall*)(ISurface*, int, vertex_t*, bool);
		return (*(original_fn**)this)[106](this, vertex_count, vertex, clip_vertices);
	}

	void draw_outlined_circle(int x, int y, int radius, int segments) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[103](this, x, y, radius, segments);
	}

	void draw_set_texture_file(int texture_id, const char* texture_name, int hardware_filter, bool force_reload = 0) {
		using original_fn = void(__thiscall*)(ISurface*, int, const char*, int, bool);
		return (*(original_fn**)this)[36](this, texture_id, texture_name, hardware_filter, force_reload);
	}

	bool is_texture_id_valid(int texture_id) {
		using original_fn = bool(__thiscall*)(ISurface*, int);
		return (*(original_fn**)this)[42](this, texture_id);
	}

	void surface_get_cursor_pos(int& x, int& y) {
		using original_fn = void(__thiscall*)(ISurface*, int&, int&);
		return (*(original_fn**)this)[100](this, std::ref(x), std::ref(y));  //x, y
	}

	void draw_textured_rect(int x, int y, int width, int height) {
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[41](this, x, y, width, height);
	}
};