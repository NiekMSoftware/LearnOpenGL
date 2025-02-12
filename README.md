# Ludus Core

Ludus Core is a leightweight game engine built with C++ and OpenGL. 
It provides a minimalistic framework for creating games using GLFW for window management and OpenGL for rendering.

This engine takes inspiration from the old Source and Doom games, this project is also mainly intended for my  
personal development and growth, so don't expect any fancy features implemented.

This engine was developed to be cross-platform compatible, if you run into any issues please let me know.

## Features
- C++23
- OpenGL 4.6 support
- GLFW-based window management

## Building
Ludus Core uses CMake as its build system. Follow these steps to build the project:
1. Clone the repository
```bash
git clone https://github.com/niekmsoftware/ludus-core.git
cd ludus-engine
```
2. Create a `build` directory and navigate into it
```bash
mkdir build
cd build
```
3. Run CMake to generate the build files:
```bash
cmake ..
```
> If you want to specify a particular generator, use:
```bash
cmake -G "YOUR PREFERED GENERATOR" ..
```
4. Build the project:
```bash
cmake --build .
```
> Alternatively, if using Makefiles:
```bash
make
```
5. Run the executable:
```bash
./LudusCore
```

## Contact
For any inquiries, reach out to `niekmsoftware@gmail.com` or open an issue in this repository.