// Copyright 2026 Ahmet Ilten. See ../../LICENSE.md for Orta terms.
#pragma once
#include "scene/gui/panel_container.h"

class EditorMainScreen;
class Label;
class LineEdit;
class RichTextLabel;

class OrtaWorkspace : public PanelContainer {
	GDCLASS(OrtaWorkspace, PanelContainer);
	EditorMainScreen *screen = nullptr;
	RichTextLabel *conversation = nullptr;
	LineEdit *prompt = nullptr;
	Label *status = nullptr;
	bool started = false;
	void _project_ready(bool p_changed);
	void _play();
	void _submit(const String &p_text);

public:
	explicit OrtaWorkspace(EditorMainScreen *p_screen);
};
