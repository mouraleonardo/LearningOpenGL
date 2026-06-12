# LearningOpenGL

Learning OpenGL with C++ as part of my Game Engine Foundations studies.

---

# About

This repository contains my exercises, experiments, and projects while learning modern OpenGL and real-time rendering concepts using C++.

The goal is to build a strong foundation for graphics programming and future game engine development.

---

# Current Project

Tank Battle is a top-down 2D tank combat prototype built with Modern OpenGL.

Current features include:

- Player-controlled tank
- Enemy AI patrol and chase behavior
- Projectile combat
- Procedural battlefield generation
- Destructible and indestructible obstacles
- Collision detection
- Custom rendering pipeline
- OpenGL 3.3 Core Profile
- GLFW input system
- GLEW extension loading
- GLM mathematics and transformations

The project is being developed incrementally as part of the Game Engine Foundations course.

---

# Topics Covered

- OpenGL basics
- Graphics pipeline
- Rendering primitives
- Vertex data
- VAO / VBO
- Shaders
- Transformations
- Coordinate Spaces
- Model / View / Projection (MVP)
- Delta Time
- Frame-Independent Motion
- Input Systems
- Collision Detection
- Orthographic Projection
- Basic AI
- Procedural Generation
- Camera systems
- Lighting
- Textures

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

