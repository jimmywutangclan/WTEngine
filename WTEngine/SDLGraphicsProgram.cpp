#include "SDLGraphicsProgram.hpp"
#include <iostream>

// Constructor
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) {
	width = w;
	height = h;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Init error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// We want to request a double buffer for smooth updating.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create window
	window = SDL_CreateWindow("WTEng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create OpenGL Context within our window
	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) {
		std::cout << "OpenGL Context error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Initialize GLAD GL library
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cout << "GLAD initialization error" << std::endl;
		exit(EXIT_FAILURE);
	}

}

// Destructor
SDLGraphicsProgram::~SDLGraphicsProgram() {
	// delete the memory address containing the window
	SDL_DestroyWindow(window);

	SDL_Quit();
}