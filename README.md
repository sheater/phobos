# Phobos (OpenGL demo)

## Intro

This project is written especially for subject PV112 at Masaryk University. It is kinda space shooter like game but currently unplayable due to missing game rules, more enemies, bonuses, etc. Main purpose is to present some OpenGL skills and have fun with development of this.
Maybe in future this will be refactored, extended, ported to Vulkan or something. Please don't throw stones at me.

![](https://github.com/skove/phobos/blob/master/screenshots/1.png)
![](https://github.com/skove/phobos/blob/master/screenshots/2.png)
![](https://github.com/skove/phobos/blob/master/screenshots/3.png)

## Features
### Engine capabilities
- Loading models from COLLADA files
- Loading textures with FreeImage lib
- Caching assets (nothing is loaded twice)
- Particle system with simple physics
- Multiple diffuse lights
- Playing sounds from WAV format
- Playing music from Vorbis OGG files (unfinished)
- Bounding box collisions
- Bitmap font rendering
- Input handling with key bindings
- Flat shading model rendering

### Game features
- Intro screen
- Loading level from XML file
- Moving enemies
- Player can shoot
- Shoot can hit enemy which suddenly explodes
- Background with moving stars (using particle system)
