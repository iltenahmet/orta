# Orta: project recap and next milestones

Updated: 2026-09-23.

## Product decisions

- An AI-only game engine for serious creative developers, working alone or in teams of 1–5.
- Source-available; the current terms are in [LICENSE.md](LICENSE.md).
- One application built directly inside a Godot fork: game view and AI conversation, with very few buttons.
- The agent harness is integrated into the application. No separate desktop shell or bridge service.
- Agents handle code, scenes, assets, shaders, debugging, playtesting and exports. Visual quality and game feel are core requirements.
- C++ is the engine foundation. C# is excluded. Gameplay scripting remains undecided between GDScript, Python and C++.
- Evaluate scripting choices on actual AI edit–run–debug tasks, including repair cycles; Python familiarity alone does not settle the choice.

See [godot-ai-only-architecture.md](godot-ai-only-architecture.md) for the architecture decisions. Earlier exploratory notes may contain superseded choices; this recap and the architecture document reflect the current direction.

## Current implementation

The complete Godot 4.7.2-stable source is imported under `engine/`, including the traditional editor UI. A first native C++ workspace displays an agent pane and an embedded game view, bypassing the project manager on a normal Mac launch. The agent is not connected to a model and has no tools yet; this is a layout prototype. Title-bar overlap, prompt text encoding and game-view sizing still need attention. The import is a source snapshot without upstream Git history. Its provenance and upstream licenses are recorded in [GODOT_UPSTREAM.md](GODOT_UPSTREAM.md).

The initial Apple Silicon build and Mac app packaging succeeded on 2026-09-23 in 8 minutes 50 seconds. Headless startup and signature verification passed, and the app was opened. See [BUILDING.md](BUILDING.md) for the command and launch path.

## Next milestones

1. **Done:** compile and launch the unmodified engine to establish a working baseline.
2. Preserve upstream Git history through a subtree before substantial customization. This was discussed but has not been implemented.
3. Refine the initial workspace and connect its conversation panel to one model. See [MINIMAL_INTERFACE.md](MINIMAL_INTERFACE.md) for the minimal two-pane implementation and remaining work.
4. Let the agent edit a project, run it, read errors, inspect screenshots and game state, and undo changes through checkpoints.
5. Demonstrate reliable creative iteration using a small Lost War-style duel, including shaders, animation, sound and frame-time feedback.

## First demonstration

The proposed test game has one board, two champions, six cards per player, resource generation, card movement, abilities, attacks and a win condition. Start with local play against a basic bot. Include a small custom-card creation flow; online accounts, matchmaking and the complete card builder can follow.

Acceptance scenario: ask the engine to “add a card that steals mana and give it a purple lightning effect.” The agent implements it, runs a reproducible encounter, catches errors, and lets the creator play, request another change and undo it without using the traditional editor.

This validates the authoring loop. Larger 3D worlds and the long-term hardware ambitions require subsequent validation.
