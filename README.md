# CG-Lab — Computer Graphics (OpenGL)

Coursework and lab exercises for **Computer Graphics**, implemented in **C++** using **OpenGL** with **GLUT** for windowing and input. Programs use **2D orthographic projection** and **immediate-mode** drawing (`glBegin` / `glEnd`) to study primitives, classic raster algorithms, simple animation, and a larger integrated scene for the term project.

---

## Technologies

| Piece | Role |
|--------|------|
| **C++** | Source language |
| **OpenGL** | 2D rendering API |
| **GLUT / FreeGLUT** | Window creation, event loop, keyboard input |
| **GLU** | Helpers such as `gluOrtho2D` for 2D coordinate setup |

Most lab sources include `<GL/glut.h>` and are straightforward to compile on **Windows** or **Linux** once GLUT is installed. The course project targets **Windows** (see below).

---

## Repository layout

```
CG-Lab/
├── lab1/   … Primitives & basic lab tasks
├── lab2/   … Lab test
├── lab3/   … Circles
├── lab4/   … DDA & Bresenham lines
├── lab5/   … Midpoint circle & motion
├── lab6/   … Animation & smiley
├── lab7/   … Lab tests A & B
└── project/
    └── smart-village.cpp   … Term project: “Smart Village”
```

---

## Lab exercises (overview)

### Lab 1 — OpenGL primitives

Introduces basic drawing modes and vertex specification in 2D:

- **`GL_POINTS`**, **`GL_LINES`**, **`GL_LINE_LOOP`**, **`GL_LINE_STRIP`**
- **`GL_TRIANGLES`**, **`GL_QUADS`**
- Setting colors, clearing the framebuffer, and mapping screen space with `gluOrtho2D`

Also includes **`LabTask01.cpp`** and **`LabTask02.cpp`** for assigned tasks on top of the demos.

### Lab 2

- **`LabTest.cpp`** — Lab assessment / integration exercise for material covered so far.

### Lab 3 — Circles

- Circle construction (e.g. polygon approximation with trig)
- Filled vs outline-style work in **`02-filled-circle.cpp`**
- **`LabTask01.cpp`** for additional circle-related tasks

### Lab 4 — Line algorithms (raster)

Classic line generation on a discrete grid:

- **DDA (Digital Differential Analyzer)** — incremental stepping along x and y
- **Bresenham’s algorithm** — integer-only decisions for efficient line rasterization

These labs visualize the algorithms by plotting points with OpenGL.

> **Note:** `bresenham's-algorithm.cpp` has an apostrophe in the filename; quote the path when compiling from a shell.

### Lab 5

- **Midpoint circle algorithm** — raster circle drawing without trig in the inner loop
- **Moving triangle** — simple motion using transforms and redraw (`01-moving-triangle.cpp`)

### Lab 6 — Animation & shapes

- **Bouncing ball** — position update per frame, boundary checks, continuous animation
- **Smiley face** — composed from circles and primitives
- **`LabTask01.cpp`** — further lab tasks

### Lab 7

- **`LabTestA.cpp`**, **`LabTestB.cpp`** — structured lab tests covering the course units.

---

## Course project: Smart Village

**File:** `project/smart-village.cpp`  
**Window title:** `Smart Village Project`  
**Default size:** 1200×750 (position 50, 50)

This is a single-file OpenGL/GLUT application that renders a **panoramic 2D village** with layered scenery, time-of-day styling, and several independent motions. It builds on ideas from the labs (polygons, circles, midpoint circle, animation) at a larger scale.

### What’s in the scene

- **Sky** — Vertical **color gradient** that interpolates between day and night palettes using a sine-driven parameter (`day_angle`), so the atmosphere shifts smoothly between bright day and darker night tones.
- **Sun** — Celestial body tied to the same day/night logic for consistent lighting mood.
- **Distant backdrop** — Snow-capped **hills**, **windmills** (with rotating blades), scattered **houses**, and **clouds** at different depths.
- **Village & nature** — Rolling green **tilla** terrain, multiple **trees**, **fields**, and a **road** through the village.
- **River** — Water band with **animated waves / ripples** (`wave_offset` scrolling) for a moving-water effect.
- **Vehicles & motion** (when animation is playing):
  - **Airplane** — flies across the scene on a loop.
  - **Motorboat** and **sailboat** — move along the river (with mirrored drawing via `glScalef` where used).
  - **Clouds** — several layers drifting at different speeds.
  - **Windmills** — blade rotation driven by the same animation tick.

### Implementation highlights

- **`gluOrtho2D`** for a fixed 2D world (roughly 0–1000 in x, extended y for ground and river).
- **Helper geometry:** `circle()` (trig-based polygon), **`midpoint_circle()`** (midpoint circle raster using small quads).
- **Transforms:** `glPushMatrix` / `glPopMatrix`, `glTranslatef`, `glScalef` to place and flip objects.
- **Animation:** `glutIdleFunc` callback updates positions and angles, then `glutPostRedisplay()` refreshes the view.
- **Keyboard** controls (see next section).

### Controls

| Key | Action |
|-----|--------|
| **Space** | Toggle **play / pause** (starts or stops the idle animation) |
| **+** or **=** | **Increase** animation speed |
| **-** or **_** | **Decrease** animation speed (clamped so it does not go below zero) |
| **T** or **D** (any case) | **Toggle** between **day** and **night** (snaps sky/sun state) |

After launch, press **Space** to start motion if the scene appears static.

---

## Requirements (general)

- **C++ compiler** — MSVC, MinGW-w64, or GCC (Clang is usually fine too).
- **OpenGL** + **GLUT** (often **FreeGLUT**) + **GLU** libraries and headers on the compiler’s search path.

On Windows, install **freeglut** (or your course bundle), then point your IDE or command line at its `include` and `lib` folders.

---

## Suggested workflow

1. Work through **lab1 → lab7** in order to align with typical CG curricula (primitives → circles → lines → advanced raster → animation → tests).
2. Use **`project/smart-village.cpp`** as the capstone: compare its structure (layered `display`, shared animation function, keyboard handling) with the smaller labs.

If this repo is shared for coursework, add your **course code**, **institution**, or **academic integrity** notes in this file as your instructor requires.
