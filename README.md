# Computer Graphics Lab (CG-Lab)

A collection of OpenGL/GLUT-based Computer Graphics lab exercises and a final course project.

The repository contains:
- Progressive lab work from basic primitives to classic drawing algorithms and animation.
- A full-scene **Smart Village** project with animated environmental elements.

## Repository Structure

- `lab1/` - OpenGL primitive drawing and introductory tasks
- `lab2/` - Lab test work
- `lab3/` - Circle drawing and filled circle tasks
- `lab4/` - Line drawing algorithms (DDA and Bresenham)
- `lab5/` - Midpoint circle and simple animation
- `lab6/` - Bounce animation, smiley scene, and lab task
- `lab7/` - Lab test programs
- `project/` - Smart Village project sources

## Lab Details

### Lab 1: OpenGL Basics

Focus: understanding immediate mode drawing and primitive types.

Files:
- `lab1/01-GL_POINTS.cpp`
- `lab1/02-GL_LINES.cpp`
- `lab1/03-GL_LINE_LOOP.cpp`
- `lab1/04-GL_LINE_STRIP.cpp`
- `lab1/05-GL_TRIANGLES.cpp`
- `lab1/06-GL_QUADS.cpp`
- `lab1/LabTask01.cpp`
- `lab1/LabTask02.cpp`

### Lab 2: Lab Test

Files:
- `lab2/LabTest.cpp`

### Lab 3: Circle Drawing

Focus: circle construction and shape filling.

Files:
- `lab3/01-circle.cpp`
- `lab3/02-filled-circle.cpp`
- `lab3/LabTask01.cpp`

### Lab 4: Line Drawing Algorithms

Focus: classic raster line algorithms.

Files:
- `lab4/dda-algorithm.cpp`
- `lab4/bresenham's-algorithm.cpp`

### Lab 5: Midpoint and Motion

Files:
- `lab5/midpoint-circle-drawing.cpp`
- `lab5/01-moving-triangle.cpp`

### Lab 6: Animation and Scene Practice

Files:
- `lab6/01-bounce-ball.cpp`
- `lab6/02-smiley-face.cpp`
- `lab6/LabTask01.cpp`

### Lab 7: Lab Tests

Files:
- `lab7/LabTestA.cpp`
- `lab7/LabTestB.cpp`

## Project Details

The `project/` folder currently contains **two** source files (the AI-enhanced build is a single file—Windows treats `smart-village-ai.cpp` and `smart-village-AI.cpp` as the same path):

- `project/smart-village.cpp` — original baseline scene
- `project/smart-village-ai.cpp` — expanded version with day/night, extra motion, and richer controls (often referred to as the “AI” variant)

### `smart-village.cpp` (Core/Original Smart Village)

This is the baseline full-scene village implementation and the main non-AI version.

Key characteristics:
- Builds a complete 2D rural landscape using layered rendering (sky, sun, hills, tilla/terrain, houses, trees, road, river, and foreground vegetation).
- Uses reusable drawing models and instance-placement functions to assemble the scene (for example cloud, hill, tree, and house models positioned at multiple locations).
- Includes continuous animation for:
  - Windmill blade rotation
  - Two clouds drifting across the sky
  - One airplane moving right-to-left with wrap-around
  - Two sailboats moving in opposite directions
- Uses a simple interaction model:
  - `Space` toggles animation play/pause
- Keeps a fixed daytime visual style (no day/night transition in this version).

### `smart-village-ai.cpp` (Enhanced / AI-assisted variant)

This is the larger, later revision of the scene (often developed or refined with AI assistance). Compared to `smart-village.cpp`, it adds:

- 2D village environment with layered composition (sky, hills, roads, river, trees, houses).
- Day/Night atmosphere control via dynamic sky and sun/moon coloring.
- Animated scene elements including:
  - Cloud movement
  - Windmill rotation
  - Airplane motion
  - River wave scrolling
  - Motorboat and sailboat movement
- Uses OpenGL immediate mode with GLUT callbacks (`display`, `keyboard`, `idle`).

### Interactive Controls (`smart-village-ai.cpp`)

- `Space` - Toggle play/pause animation
- `+` / `=` - Increase animation speed
- `-` / `_` - Decrease animation speed
- `T` / `D` - Toggle day/night mode

## Build and Run (Windows + GLUT)

This repository uses C++ with OpenGL/GLUT style headers (`windows.h`, `GL/glut.h`, `GL/glu.h`).

### Option A: Code::Blocks / Visual Studio (recommended)

1. Create a C++ project.
2. Add the selected `.cpp` file (lab or project) to the project.
3. Link GLUT/OpenGL libraries (commonly `opengl32`, `glu32`, and `glut32`/`freeglut`).
4. Build and run.

### Option B: g++ (MinGW example)

If GLUT/freeglut is configured in your environment:

```bash
g++ "project/smart-village-ai.cpp" -o smart-village -lopengl32 -lglu32 -lglut32
./smart-village
```

Library names may vary depending on your GLUT setup (`glut32` vs `freeglut`).

## Notes

- This codebase primarily uses classic OpenGL immediate mode for educational learning.
