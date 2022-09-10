#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

// C++ Libraries
#include "SDL2/SDL.h"
#include "glad/glad.h"

// Standard stuff
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class SDLGraphicsProgram {
public:
    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Loop
    void Loop();
    // Set up shaders
    bool SetupShaders();
    // Load shader from glsl file to String
    std::string LoadShader(std::string dir);
private:
    unsigned int width;
    unsigned int height;
    SDL_Window* window;
    SDL_GLContext glContext;


    // Temporary for base triangle
    std::vector<float> vertexArray;

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
};


#endif