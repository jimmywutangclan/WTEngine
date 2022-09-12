#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

// C++ Libraries
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "stb/stb_image.h"

// Standard stuff
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

const unsigned int attr_size = 5;

class SDLGraphicsProgram {
public:
    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Render images
    void Render();
    // Loop
    void Loop();
    // Set up shaders
    unsigned int SetupShaders();
    // Load shader from glsl file to String
    std::string LoadShader(std::string dir);
private:
    unsigned int width;
    unsigned int height;
    SDL_Window* window;
    SDL_GLContext glContext;


    // Temporary for base square
    std::vector<float> vertexArray;
    std::vector<unsigned int> indexArray;
    unsigned int texture;
    unsigned int texture2;

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    unsigned int program;
};


#endif