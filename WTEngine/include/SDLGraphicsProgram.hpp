#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

// C++ Libraries
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
    // Load cube properties
    void LoadCube(std::string texture);
    // Create, Update and Bind uniform Model, View and Projection matrices for the cube
    void UpdateCube(float x, float y, float z);
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


    // Temporary for base cube
    std::vector<float> vertexArray;
    std::vector<unsigned int> indexArray;
    unsigned int texture;
    float curr_angle;

    // VBO, VAO, and EBO
    // VBO and EBO are the arrays for vertices/indices associated with our cube
    // VAO stores attributes for how to interpret each vertex
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    unsigned int program;
};


#endif