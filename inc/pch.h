#pragma once

#define APP_NAME "Learn OpenGL"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define VSYNC 1

// GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// common
#include <vector>
#include <string>
#include <memory>

// io
#include <fstream>
#include <sstream>
#include <iostream>
#include <format>
#include <print>

// timer
#include <chrono>
#include <thread>

// custom GL 
#include "shader.h"