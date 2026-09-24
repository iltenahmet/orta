# AI-only Godot architecture

Decision recorded: 2026-09-19.

Licensing decision confirmed: 2026-09-21. The product will be source-available; see LICENSE.md for the current Orta terms. Retain Godot's license and third-party notices for reused code.

Build the product directly inside a Godot fork. Replace the traditional editor interface with Godot's own UI showing the game and an AI conversation window, with very few buttons. The entire authoring experience is AI-only.

Keep the architecture simple: one application and one codebase. The agent harness lives inside the application, calls model APIs, and accesses Godot's systems directly. It edits project files, manipulates scenes, creates and imports assets, writes shaders, runs and stops the game, and inspects results.

Do not introduce a separate TypeScript desktop shell, external harness process, or standalone bridge service. Internal communication with the running game is still necessary, but stays within the application's architecture. One application does not require putting the editor and running game in the same process.

Visual quality and game feel are core requirements. The agent should iterate on shaders, lighting, materials, animation, audio, camera behavior and gameplay timing using rendered output, playtesting and performance feedback. These capabilities should be integrated into the same simple interface.

Language direction updated: 2026-09-21. C# is excluded. C++ is the engine foundation. The gameplay language remains open: C++-only, native GDScript, and Python are being considered. The user's concern is whether AI can generate and repair Python more reliably than GDScript. Evaluate complete edit-run-debug tasks rather than assuming that language familiarity alone settles the choice. No Python runtime integration has been added. Godot's existing Python/SCons build tooling is separate from this runtime language choice. GPU shader languages remain available.
