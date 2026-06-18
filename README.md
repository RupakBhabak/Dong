# 🏓 Dong - Pong Clone in C++ & Raylib

A simple Pong-style arcade game built with **C++** and **Raylib**. Control the left paddle, compete against an AI-controlled opponent, and try to achieve the highest score.

## 🎮 Gameplay

- Player controls the left paddle using:
  - **W** or **UP** → Move Up
  - **S** or **Down** → Move Down
- The AI controls the right paddle.
- The ball bounces off paddles and screen boundaries.
- Each successful paddle hit increases the ball's speed.
- The AI gradually becomes faster as the game progresses.
- A point is awarded when the ball passes an opponent's paddle.
- Scores are displayed at the top of the screen.

## ✨ Features

- Smooth frame-independent movement
- AI-controlled opponent
- Dynamic difficulty scaling
- Score tracking system
- Collision detection
- Increasing game speed over time
- Built with Raylib for lightweight graphics rendering

## 🛠️ Technologies Used

- **C++**
- **Raylib**

### Main Components

| Class | Description |
|---------|-------------|
| `Ball` | Handles ball movement, collisions, and rendering |
| `Paddle` | Player paddle logic and controls |
| `MultiplayerPaddle` | AI paddle implementation |
| `Score` | Manages player and AI scores |

## 🚀 Getting Started

### Prerequisites

Install:

- C++ Compiler (GCC, Clang, or MSVC)
- Raylib Library

### Clone the Repository

```bash
git clone https://github.com/yourusername/dong.git
cd dong
```

### Build

#### Linux

```bash
g++ main.cpp -o dong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

#### Windows (MinGW)

```bash
g++ main.cpp -o dong.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

#### macOS

```bash
g++ main.cpp -o dong -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

### Run

```bash
./dong
```

## 🎯 Controls

| Key | Action |
|------|--------|
| W or UP | Move paddle up |
| S or DOWN | Move paddle down |
| ESC | Exit game |

## ⚙️ Game Mechanics

### Ball Speed Increase

Each paddle collision:

- Reverses ball direction.
- Increases horizontal speed.
- Increases vertical speed.
- Gradually raises game difficulty.

### AI Difficulty Scaling

As rallies become longer:

- AI paddle speed increases.
- Player paddle speed also receives boosts.
- Matches become progressively more challenging.

## 📄 License

This project is licensed under the MIT License.

## 👨‍💻 Author

Rupak Bhabak

Created using **C++** and **Raylib** as a learning project to explore game development fundamentals such as:

- Object-Oriented Programming
- Collision Detection
- Game Loops
- AI Movement
- Real-Time Rendering

---

⭐ If you found this project useful, consider giving it a star!
