# Cubestacle SDL

Cubestacle is a lightweight 3-D endless-runner written in portable C 99 on top of  
**SDL2**, **OpenGL 1.x (fixed-function)** and a handful of self-contained utilities.  
You steer a brave red cube that sprints forward on an infinite strip of ground,  
dodging randomly generated obstacles and collecting rotating gold coins.  
The longer you survive the faster you go—your score is simply the distance run.

---

## 1 · Build & Run

| Platform | Dependencies                                                                                                            | Typical install command¹                                     |
|----------|-------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------|
| **Windows (64-bit MinGW-w64)** | *SDL2*, *SDL2_image*, `opengl32`, `glu32`, `gdi32`, `mingw32`                                      | Pre-built development ZIPs from <https://libsdl.org>         |
| **Linux (GCC / Clang)**       | `libsdl2-dev`, `libsdl2-image-dev`, `libgl1-mesa-dev`, `libglu1-mesa-dev`, `make`, `pkg-config`    | `sudo apt install libsdl2-dev libsdl2-image-dev …`           |
| **macOS (Homebrew)**          | `sdl2` `sdl2_image` (uses system OpenGL)                                                           | `brew install sdl2 sdl2_image`                               |

> ¹ Package names may vary slightly between distros.

```bash
git clone https://github.com/your-user/cubestacle-sdl.git
cd  cubestacle-sdl
make                # or "mingw32-make" on Windows
./CubestacleSDL     # on Linux/macOS
CubestacleSDL.exe   # on Windows
````

The **Makefile** detects the host OS; override variables if your layout differs:

```bash
make CC=clang SDL_CFLAGS=`sdl2-config --cflags` SDL_LDLIBS=`sdl2-config --libs`
```

---

## 2 · Controls

| Action                | Key / Mouse             |
| --------------------- | ----------------------- |
| Move left / right     | **A / D** or **← / →**  |
| Tilt camera up / down | **W / S** or **↑ / ↓**  |
| Zoom camera           | Mouse wheel             |
| Return to main menu   | **Esc**                 |
| Quit                  | **Quit** button in menu |

---

## 3 · Gameplay

* The cube accelerates until it reaches a top speed of **40 units/s**.
* Score = floor of the cube’s **X coordinate**.
* Hitting an obstacle **or** falling off the track ends the run.
* Coins bob up and down; colliding with one adds to your **coin counter**.
* Every \~20- 25 units a new obstacle is spawned; coins appear every 8-12 units.
* Obstacle colours cycle every **150 score** to hint at progress.

---

## 4 · Code Layout

```
├── assets/           # textures, bitmaps, fonts (only ground.bmp now)
├── include/          # public headers
├── src/              # implementation (.c) files
│   ├── app.c         # high-level SDL & main loop
│   ├── camera.*      # orbit camera utilities
│   ├── scene.*       # world orchestration (spawning, collisions)
│   ├── player.*, coin.*, obstacle.*, ground.*
│   ├── skybox.*      # static colour-gradient sky
│   └── menu.*, info.*, gameover.*  # UI screens
└── Makefile
```

*The project is intentionally single-library; no external math or GL loader is
required.  Modern GL calls are avoided so that `opengl32.dll` on Windows
(1.1) still links; texture formats are selected at run-time for Intel/NVIDIA
parity.*

---

## 5 · Customising

* **Textures** – Replace `assets/ground.bmp` with any power-of-two BGRA
  bitmap (e.g. 1024×1024).
* **Sky colours** – Edit the gradient in `src/skybox.c → sky_color()`.
* **Physics & speeds** – Tunables live in `player.c` and the constants at the
  top of `scene.c`.

---

## 6 · Troubleshooting

| Symptom                          | Cause / Fix                                                                                                                                 |
| -------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| White ground / sky on Intel iGPU | Ensure the driver supports OpenGL 4.x.  The ground texture loader converts to **BGRA8888 + GL\_BGRA**, and coordinates never exceed 4096.   |
| Texture tinted red               | Mismatch between SDL surface format and `glTexImage2D` parameters. Always keep the pair **BGRA8888 ↔ GL\_BGRA** or **RGBA8888 ↔ GL\_RGBA**. |
| Linking error `glGenerateMipmap` | Windows’ `opengl32` exports only 1.1; either keep the no-mipmap path (default) or load the function pointer manually.                       |

---

## 7 · License

CubestacleSDL is released under the **MIT License** – see `LICENSE` for details.

---

## 8 · Credits

* **Simple DirectMedia Layer 2** – [https://libsdl.org](https://libsdl.org)
* **SDL\_image** – image codec helpers
* Ground texture: *public-domain wood planks* by **Kenney.nl**
* All code & remaining art © 2025 Your Name

```
```
