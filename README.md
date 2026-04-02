# Spartanoid

A ball-and-paddle game built in C++ using wxWidgets, developed as part of CSE335 at Michigan State University.

## Gameplay

Control the paddle using your keyboard to bounce the ball and destroy all the bricks as fast as possible.

| Key | Action |
|-----|--------|
| ← Arrow / A | Move paddle left |
| → Arrow / D | Move paddle right |
| Click ball | Launch ball |

## Features

- **4 Levels** — Levels 1 and 2 are provided; Level 3 is a custom team-designed level
- **Scoreboard** — Tracks elapsed time (M:SS) and score per level, resets on level change
- **Bricks** — Destroy bricks to earn points; each brick is worth 10 points
- **Power-up (Sparty)** — Ball collision doubles your score and spawns a second ball
- **Coins** — 20% chance to spawn when a brick is destroyed; catch with the paddle for bonus points
- **Enemy** — Moves left and right at the top of the screen; ball collision shows "You Lose!" and restarts the level
- **Virtual pixel scaling** — Game scales to any window size

## Levels

| Level | Description |
|-------|-------------|
| 0 | Dev/test level |
| 1 | Standard layout with power-up |
| 2 | Adds enemy and coin mechanics |
| 3 | Custom team level |

Switch levels anytime using the **Levels** menu.

## Building

**Requirements**
- CMake 3.15+
- wxWidgets
- C++17

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Project Structure

```
project1/
├── SpartanoidLib/       # Game library (all game classes)
│   ├── Ball             # Ball physics and collision
│   ├── Brick            # Brick item, score on hit
│   ├── Coin             # Animated coin, gravity, paddle catch
│   ├── Enemy            # Left/right patrol, triggers lose state
│   ├── Paddle           # Player-controlled paddle
│   ├── PowerUp          # Score doubler + second ball spawn
│   ├── ScoreBoard       # Timer and score display
│   ├── Level            # XML level loader
│   └── Spartanoid       # Main game controller
├── Tests/               # Unit tests (Google Test)
├── images/              # Game assets
├── levels/              # XML level definitions
└── CMakeLists.txt
```

## Team

Developed by Team Inverter — CSE335, Michigan State University, Spring 2026.
