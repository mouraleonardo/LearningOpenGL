# LearningOpenGL

Learning OpenGL with C++ as part of my Game Engine Foundations studies.

---

# About

This repository contains my exercises, experiments, and projects while learning modern OpenGL and real-time rendering concepts using C++.

The goal is to build a strong foundation for graphics programming and future game engine development.

---

# Current Project

## First-Person Medieval Environment

A 3D first-person medieval environment built with Modern OpenGL as part of the Game Engine Foundations course.

Current features include:

- First-person camera with mouse look
- Modern OpenGL 3.3 Core Profile rendering
- Model, View, and Projection (MVP) transformations
- Procedurally generated forest
- Multiple procedural tree types
- Medieval castle
- Collision detection
- Interactive animated door
- Interactive treasure chests
- Object-oriented game architecture
- Modular rendering pipeline
- GLFW input handling
- GLEW extension loading
- GLM mathematics and transformations

---

# Topics Covered

- Modern OpenGL
- Graphics Pipeline
- Vertex Data
- VAO / VBO / EBO
- GLSL Shaders
- Mesh Rendering
- Model / View / Projection (MVP)
- Coordinate Spaces
- Perspective Projection
- Depth Testing
- Texture Mapping
- Camera Systems
- Frame-Independent Animation
- Delta Time
- Object-Oriented Programming (OOP)
- Collision Detection
- Procedural Modeling
- Procedural Generation
- Scene Management
- Interactive Objects
- Transformations
- OpenGL Rendering Pipeline

---

# Technologies

- C++
- OpenGL
- GLFW
- GLEW
- GLM
- Visual Studio

---

# Progress

## Week 1

- Setup GLFW and GLEW
- Create OpenGL window
- Implement render loop
- Clear screen and swap buffers
- Render:
  - Triangle
  - Square
  - Circle
- Learn legacy OpenGL rendering

---

## Week 2

- Setup VAO and VBO
- Add vertex data for rendering
- Learn modern OpenGL graphics pipeline
- Create shader program
- Render first triangle using Modern OpenGL

---

## Week 3

- Create a rotating triangle using transformation matrices
- Add RGB vertex colors and pass color attributes to shaders
- Learn how vertex and fragment shaders work together for color interpolation
- Use Object-Oriented Programming (OOP) to organize OpenGL code into classes
- Render an animated rotating RGB triangle using Modern OpenGL

---

## Week 4

- Implemented 3D cube rendering using Modern OpenGL
- Created a Mesh class using VAO, VBO, and EBO for indexed rendering
- Added indexed cube geometry with RGB vertex colors
- Developed a Shader class for GLSL shader compilation and management
- Implemented a Renderer class with Model, View, and Projection (MVP) transformations
- Integrated GLM for rotation, translation, and perspective projection matrices
- Enabled depth testing for correct 3D object rendering
- Added vertex and fragment shaders with RGB color interpolation
- Applied Object-Oriented Programming (OOP) principles to organize rendering components
- Structured the project using separate Headers, Shaders, and Dependencies folders

---

## Week 5

- Implemented an animated vehicle using Modern OpenGL transformations and shader effects
- Applied fundamental computer graphics concepts including translation, rotation, scaling, and orthographic projection
- Developed time-based animations for realistic object movement
- Created a moving vehicle with independently rotating wheels
- Added animated smoke effects using transformation and shader techniques
- Utilized GLSL shaders and uniform variables for dynamic rendering
- Implemented mesh rendering using VAO, VBO, and indexed geometry
- Integrated GLM for transformation matrix calculations
- Built the project using OpenGL 3.3, GLFW, GLEW, and GLM
- Continued applying Object-Oriented Programming (OOP) principles for modular and maintainable code

---

## Week 6

- Developed a complete Tank Battle prototype using Modern OpenGL
- Implemented a game architecture based on Object-Oriented Programming (OOP)
- Created a player-controlled tank with rotation, movement, and shooting mechanics
- Added enemy AI with patrol and chase behaviors using a simple state machine
- Implemented projectile systems for both player and enemy tanks
- Developed procedural battlefield generation with randomized obstacle placement
- Added destructible brick blocks and indestructible steel obstacles
- Implemented collision detection for tanks, bullets, and environment objects
- Built a custom Renderer system using Model, View, and Projection (MVP) transformations
- Applied orthographic projection for 2D gameplay rendering
- Implemented frame-independent movement using Delta Time
- Added real-time keyboard input handling using GLFW
- Learned and applied Coordinate Spaces:
  - Model Space
  - World Space
  - View Space
  - Projection Space
- Used GLM for transformation matrices and vector mathematics
- Continued using Modern OpenGL 3.3 Core Profile with custom GLSL shaders
- Organized the project into reusable gameplay and rendering systems:
  - Game
  - Renderer
  - Map
  - Tank
  - Enemy
  - Bullet
  - Shader
  - Mesh

---

## Week 7

- Transitioned from a 2D project to a fully 3D first-person environment
- Implemented a first-person camera with keyboard movement and mouse look
- Added perspective projection using GLM
- Implemented collision detection between the player and the environment
- Created a modular game architecture following Object-Oriented Programming (OOP) principles
- Built a medieval castle using procedural cube-based modeling
- Implemented an interactive animated castle door
- Developed a reusable Renderer class responsible for scene rendering
- Expanded the Mesh and Shader systems for 3D rendering
- Applied Model, View, and Projection (MVP) transformations throughout the engine
- Continued using Modern OpenGL 3.3 Core Profile with GLFW, GLEW, and GLM

---

## Week 8

- Expanded the medieval environment with interactive treasure chests
- Implemented smooth lid animations using frame-independent interpolation with Delta Time
- Added player interaction using keyboard input
- Designed reusable game objects following Object-Oriented Programming (OOP) principles
- Built treasure chests procedurally using cube primitives
- Implemented multiple procedural tree types
- Added randomized tree rotation, scale, trunk height, trunk width, and leaf size
- Improved the forest using procedural generation techniques
- Reinforced the separation of responsibilities between the Game, World, Renderer, and gameplay object classes
- Continued expanding the custom rendering pipeline using Modern OpenGL
- Prepared the engine architecture for future gameplay objects such as tables, chairs, weapons, decorations, and other interactive medieval assets

---

## Week 9 and 10

Implements a complete 2D survival game using modern OpenGL, GLFW,
GLEW, GLM and stb_image.

The game features an animated gangster character capable of walking, running, jumping and performing three different melee attacks. Input is supported through both keyboard and compatible gamepads.

Adds enemy AI with randomized spawning from both sides of the screen. Enemies pursue the player, attack at close range, receive damage and die after three successful hits. Up to five enemies can appear simultaneously, with a two-second spawn interval.

Implements a player health system with five health points and a heart-based HUD. Each enemy hit removes one heart. When the player dies, the death animation finishes before displaying a centered Game Over screen with a fade-in transition. The game can be restarted with Enter or closed with Escape.

Adds synchronized audio for walking, running, randomized punch impacts, fatal hits, looping background music and the Game Over sequence. Audio code is organized into a dedicated Audio module with independent music and sound-effect playback.

Adds keyboard and gamepad controls:

- A/D or directional arrows: move
- Left Shift or LB/L1: run
- Space or A/Cross: jump
- J or X/Square: attack 1
- K or Y/Triangle: attack 2
- L or B/Circle: attack 3
- Enter: restart after Game Over
- Escape or Start/Options: exit

Organizes the project into dedicated modules for Animation, Audio, Core, Gameplay, Graphics, Input, Physics, Resources and UI.

Documents all author-owned source files, classes, functions, shaders and extension points. Third-party dependencies remain unchanged.

Main implemented features:

- OpenGL 3.3 Core Profile rendering
- Orthographic 2D camera
- Animated sprite sheets
- Frame-independent movement
- Running and jumping mechanics
- Melee combat with animation-based impact frames
- Character and enemy health systems
- Enemy pursuit and attack AI
- Randomized enemy spawning
- Refined body and attack hitboxes
- Keyboard and gamepad input
- Analog-stick dead zone
- Five-heart health HUD
- Game Over and restart flow
- Fade-in UI transition
- Background music and sound effects
- Centralized resource management
- Modular UI and audio architecture
- Complete source-code documentation

---

## Week 11 — Treasure Chest with Phong Lighting

This project demonstrates the implementation of **per-fragment Phong lighting** in an interactive 3D treasure chest using OpenGL 3.3.

The treasure chest is built procedurally by reusing a cube mesh. Instead of using two solid cubes, the base and lid are assembled from thin wall pieces, creating visible internal depth when the chest opens.

### Features

- Hollow treasure chest base
- Lid with visible internal depth
- Hierarchical lid transformation
- Smooth opening and closing animation
- Frame-independent movement using delta time
- Textured cube geometry
- Per-fragment Phong lighting
- Ambient lighting
- Lambert diffuse lighting
- Phong specular reflections
- Secondary fill light
- Subtle rim lighting
- Exposure control
- Gamma correction
- First-person camera controls

### Phong Lighting

The final lighting is calculated inside the fragment shader, producing smoother results than per-vertex lighting.

The illumination model combines three main components: glsl Phong = Ambient + Diffuse + Specular

---

# Project Structure

```text
Src/
|-- Dependencies/
|   |-- GLFW/
|   |   |-- Include/
|   |   `-- Lib/
|   |
|   |-- GLEW/
|   |   |-- Include/
|   |   `-- Lib/
|   |
|   `-- GLM/
|
|-- Headers/
|-- Shaders/
|-- Src/
|
`-- main.cpp
```

---

# Download Dependencies

## GLFW

Official website:

https://www.glfw.org/

Download the precompiled binaries for Windows.

---

## GLEW

Official website:

https://glew.sourceforge.net/

Download the Windows binaries.

---

## GLM

Official website:

https://github.com/g-truc/glm

Download the latest release and extract the files into the `Dependencies/GLM/` directory.

---

# Visual Studio Configuration

Open your project in Visual Studio.

---

# 1. Add Include Directories (.h files)

These folders contain the header files used by:

```cpp
#include <glew.h>
#include <glfw3.h>
```

## Steps

Go to:

```text
Project -> Properties
```

Then:

```text
C/C++ -> General -> Additional Include Directories
```

Add:

```text
$(ProjectDir)Dependencies\GLFW\Include
$(ProjectDir)Dependencies\GLEW\Include
```

---

# 2. Add Library Directories (.lib files)

These folders contain the `.lib` files used during linking.

## Steps

Go to:

```text
Linker -> General -> Additional Library Directories
```

Add:

```text
$(ProjectDir)Dependencies\GLFW\Lib
$(ProjectDir)Dependencies\GLEW\Lib
$(ProjectDir)Dependencies\GLM
```

---

# 3. Add Required Libraries

Now tell Visual Studio which libraries to link.

## Steps

Go to:

```text
Linker -> Input -> Additional Dependencies
```

Add:

```text
glfw3.lib
glew32s.lib
opengl32.lib
```

---

# 4. Add GLEW_STATIC Definition

If using the static version of GLEW, add:

```text
GLEW_STATIC
```

## Steps

Go to:

```text
C/C++ -> Preprocessor -> Preprocessor Definitions
```

Add:

```text
GLEW_STATIC
```

---

# 5. Include Headers in Your Code

```cpp
#include <glew.h>
#include <glfw3.h>
```

Important:

`glew.h` must be included before `glfw3.h`

---

# 6. Build the Project

Build:

```text
CTRL + SHIFT + B
```

Run:

```text
CTRL + F5
```

If everything is configured correctly, an OpenGL window should appear.

---

# Author
Leonardo Moura

