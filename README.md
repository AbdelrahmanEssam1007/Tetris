# Tetris - Arcade Game Recreation

## Overview

**Tetris** is a faithful recreation of the iconic arcade game built in **C++**, utilizing the **Raylib** graphics library for rendering and input handling. The objective was to develop a fast, responsive, and visually appealing clone of the original Tetris, while maintaining clean and modular code. The project focuses on replicating the core mechanics of the game, offering an enjoyable retro-gaming experience.

Development followed a structured approach, adding gameplay features and polish in iterative phases. This README outlines the current features, technologies used, and technical implementation details.

## Completed Features

### Phase 1: Core Gameplay

#### Basic Game Loop
*  Real-time block falling with frame-based timing.
*  Game tick advances blocks downwards unless paused or blocked.
*  Game-over state when the top of the board is reached.

#### Block Mechanics
*  Standard tetromino shapes implemented (I, O, T, S, Z, J, L).
*  Blocks rotation
*  Blocks can be moved left, right, or dropped instantly.

#### Grid Management
*  Playfield grid tracks placed blocks and cleared lines.
*  Automatic line clearing when a row is fully filled.
*  Cleared rows cause above blocks to fall down.

#### Scoring and Levels
*  Scoring system based on number of lines cleared at once.
*  Block falling speed increases with each level.

### Phase 2: UI and Interactivity

#### User Interface
*  Minimalistic interface showing current score, level, and upcoming piece.
*  Game reset functionality with key inputs.
*  Grid and tetrominoes are visually styled to match classic aesthetics.

#### Audio and Feedback
*  Sound effects for drop, and line clear
*  Music that 
### Phase 3: Extras and Optimization

*  Ghost piece (shows where the current tetromino will land).
*  Custom themes or color schemes.
*  Controller or touch input support.

## Technical Details

### Technology Stack

*   **Language:** C++
*   **Graphics/Framework:** Raylib
*   **Build System:** CMake
*   **Platform:** Cross-platform (Windows/Linux)

### Game Logic and Structure

*  Tetrominoes are represented using a 4x4 grid.
*  Rotation handled with matrix transformations or predefined states.
*  Collision detection for movement and rotation edge cases.

### Design Patterns and Practices

*  Object-oriented structure for game entities like Board, Tetromino, and Game.
*  Clean separation of rendering, input handling, and logic.
*  Focus on modularity to allow for easy expansion.

## Contributing

Contributions are welcome! Feel free to fork the repository and submit a pull request. For significant changes or new features, open an issue first to discuss your idea.

![Tetris Screenshot](https://github.com/user-attachments/assets/85c9a673-a760-4649-8e64-905d3c5fb082)
