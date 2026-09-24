# First Orta interface

Updated: 2026-09-23. The initial C++ layout is implemented; model connection and agent tools remain to be built.

One native Godot window, split left and right. Use C++ and existing Godot UI components.

- Left: an empty conversation area and a text field, labeled Agent. The current build displays the disconnected status; submitting text does not contact a model or claim to answer. Connecting a model through Godot's HTTP client is the next step.
- Right: reuse the existing embedded game view with its toolbar hidden.
- Startup: open one fixed test project, start it automatically, and hide editor menus, docks and tabs.

The first version has no application buttons, tabs, settings screen, streaming replies or additional framework. Future model connection details should come from local configuration, with credentials kept out of version control. Show request errors in the conversation. The game itself retains its normal input handling.

This is a working tool for professional creators. Keep its copy functional: Agent, Game, connection state and errors. No slogans, inspirational text, onboarding headlines, decorative sample worlds or idea-saving substitute for agent chat. An empty project shows an empty game view.

Giving the model project-editing and game-restart tools follows the actual model connection; a text reply alone does not change the game.

Relevant existing implementation: `engine/editor/editor_node.cpp`, `engine/editor/editor_main_screen.cpp`, `engine/editor/run/game_view_plugin.cpp`, and the macOS embedding implementation under `engine/platform/macos/editor/`.

Keep the existing engine systems behind the simplified interface. Avoid redesigning the game embedding or removing editor internals for the first prototype. Ensure the game and chat can each receive keyboard focus without triggering hidden editor shortcuts.
