// Copyright 2026 Ahmet Ilten. See ../../LICENSE.md for Orta terms.
#include "orta_workspace.h"

#include "core/object/callable_mp.h"
#include "editor/editor_main_screen.h"
#include "editor/file_system/editor_file_system.h"
#include "editor/run/editor_run_bar.h"
#include "editor/themes/editor_scale.h"
#include "scene/gui/box_container.h"
#include "scene/gui/label.h"
#include "scene/gui/line_edit.h"
#include "scene/gui/margin_container.h"
#include "scene/gui/rich_text_label.h"
#include "scene/gui/separator.h"
#include "scene/resources/font.h"
#include "scene/resources/style_box_flat.h"
#include "scene/resources/theme.h"

static Ref<StyleBoxFlat> surface(const Color &p_color, int p_radius = 0) {
	Ref<StyleBoxFlat> style;
	style.instantiate();
	style->set_bg_color(p_color);
	style->set_corner_radius_all(p_radius * EDSCALE);
	return style;
}

static Label *text_label(const String &p_text, int p_size, const Color &p_color) {
	Label *label = memnew(Label);
	label->set_text(p_text);
	label->add_theme_font_size_override("font_size", p_size * EDSCALE);
	label->add_theme_color_override("font_color", p_color);
	return label;
}

void OrtaWorkspace::_project_ready(bool p_changed) {
	if (!started) {
		started = true;
		callable_mp(this, &OrtaWorkspace::_play).call_deferred();
	}
}

void OrtaWorkspace::_play() {
	screen->select(EditorMainScreen::EDITOR_GAME);
	EditorRunBar::get_singleton()->play_main_scene();
	prompt->grab_focus();
}

void OrtaWorkspace::_submit(const String &p_text) {
	if (!p_text.strip_edges().is_empty()) {
		status->set_text("No model connected");
	}
}

OrtaWorkspace::OrtaWorkspace(EditorMainScreen *p_screen) : screen(p_screen) {
	const Color ink = Color::html("e9e4dc");
	const Color muted = Color::html("858782");
	add_theme_style_override("panel", surface(Color::html("161817")));
	set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	Ref<SystemFont> font;
	font.instantiate();
	font->set_font_names(PackedStringArray({ "Helvetica Neue", "Arial" }));
	Ref<Theme> workspace_theme;
	workspace_theme.instantiate();
	workspace_theme->set_default_font(font);
	workspace_theme->set_default_font_size(14 * EDSCALE);
	set_theme(workspace_theme);

	HBoxContainer *columns = memnew(HBoxContainer);
	columns->add_theme_constant_override("separation", 0);
	add_child(columns);
	MarginContainer *left = memnew(MarginContainer);
	left->set_custom_minimum_size(Size2(360, 0) * EDSCALE);
	for (const char *side : { "margin_left", "margin_right", "margin_top", "margin_bottom" }) {
		left->add_theme_constant_override(side, 20 * EDSCALE);
	}
	columns->add_child(left);
	VBoxContainer *chat = memnew(VBoxContainer);
	chat->add_theme_constant_override("separation", 16 * EDSCALE);
	left->add_child(chat);
	HBoxContainer *chat_header = memnew(HBoxContainer);
	chat->add_child(chat_header);
	Label *agent_title = text_label("Agent", 14, ink);
	agent_title->set_h_size_flags(SIZE_EXPAND_FILL);
	chat_header->add_child(agent_title);
	status = text_label("Not connected", 11, muted);
	chat_header->add_child(status);
	conversation = memnew(RichTextLabel);
	conversation->set_v_size_flags(SIZE_EXPAND_FILL);
	conversation->set_custom_minimum_size(Size2(0, 100) * EDSCALE);
	conversation->set_selection_enabled(true);
	conversation->set_scroll_follow(true);
	conversation->add_theme_color_override("default_color", muted);
	chat->add_child(conversation);
	prompt = memnew(LineEdit);
	prompt->set_placeholder("Message…");
	prompt->set_custom_minimum_size(Size2(0, 44) * EDSCALE);
	Ref<StyleBoxFlat> field = surface(Color::html("212421"), 4);
	field->set_content_margin_all(16 * EDSCALE);
	prompt->add_theme_style_override("normal", field);
	prompt->add_theme_style_override("read_only", field);
	Ref<StyleBoxFlat> focus = surface(Color(0, 0, 0, 0), 4);
	focus->set_border_width_all(1 * EDSCALE);
	focus->set_border_color(Color::html("707969"));
	prompt->add_theme_style_override("focus", focus);
	prompt->add_theme_color_override("font_color", ink);
	prompt->add_theme_color_override("font_placeholder_color", muted);
	prompt->connect("text_submitted", callable_mp(this, &OrtaWorkspace::_submit));
	chat->add_child(prompt);

	VSeparator *divider = memnew(VSeparator);
	Ref<StyleBoxFlat> line = surface(Color::html("30332e"));
	line->set_content_margin_all(0);
	divider->add_theme_style_override("separator", line);
	divider->add_theme_constant_override("separation", 1 * EDSCALE);
	columns->add_child(divider);
	MarginContainer *right = memnew(MarginContainer);
	right->set_h_size_flags(SIZE_EXPAND_FILL);
	for (const char *side : { "margin_left", "margin_right", "margin_top", "margin_bottom" }) {
		right->add_theme_constant_override(side, 20 * EDSCALE);
	}
	columns->add_child(right);
	VBoxContainer *canvas = memnew(VBoxContainer);
	canvas->add_theme_constant_override("separation", 16 * EDSCALE);
	right->add_child(canvas);
	HBoxContainer *heading = memnew(HBoxContainer);
	canvas->add_child(heading);
	Label *name = text_label("Game", 14, ink);
	name->set_h_size_flags(SIZE_EXPAND_FILL);
	heading->add_child(name);
	screen->reparent(canvas);
	screen->set_h_size_flags(SIZE_EXPAND_FILL);
	screen->set_v_size_flags(SIZE_EXPAND_FILL);
	screen->add_theme_style_override("panel", surface(Color::html("101411")));
	EditorFileSystem::get_singleton()->connect("sources_changed", callable_mp(this, &OrtaWorkspace::_project_ready));
}
