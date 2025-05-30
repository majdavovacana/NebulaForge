# NebulaForge: A 2D Cosmic Exploration-Puzzle Game

## Overview
NebulaForge is an innovative 2D exploration-puzzle game built in C++ using the SFML library. Players craft and manipulate nebulous clouds to guide a probe through cosmic hazards, such as asteroids and energy fields, to reach stellar beacons. The game combines exploration with dynamic environmental manipulation, offering a unique experience distinct from traditional puzzle or exploration games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, procedural environments, and physics-based puzzles. By sponsoring NebulaForge via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Cloud Crafting Mechanics**: Create and shape nebulous clouds to alter probe trajectories.
- **Cosmic Hazards**: Navigate through asteroids and energy fields with strategic cloud placement.
- **Minimalist Visuals**: Clean 2D graphics with glowing cosmic effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/nebulaforge.git
   cd nebulaforge
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./NebulaForge
   ```

## Gameplay
- **Objective**: Guide the probe to the stellar beacon by crafting clouds to avoid hazards.
- **Controls**:
  - **WASD**: Move the cursor to place clouds.
  - **Space**: Place a cloud.
  - **Q/E**: Adjust cloud density (affects push strength).
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Clouds push the probe based on their density. Place clouds strategically to steer the probe through asteroids and energy fields to reach the beacon.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (probe, clouds, hazards, beacon).
- `src/Game.hpp`: Core game logic, cloud mechanics, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support NebulaForge’s development through [GitHub Sponsors](https://github.com/sponsors/majdavovacana)! Your contributions fund:
- New cosmic hazards and level designs.
- Advanced cloud physics and visual effects.
- Tutorials for C++ and procedural generation.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by cosmic exploration and physics-based puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor NebulaForge to chart new stars in puzzle gaming!**
