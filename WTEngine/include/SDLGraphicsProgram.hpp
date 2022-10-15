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

// In-house code
#include "Objects/Cube.hpp"
#include "Components/Camera.hpp"
#include "Components/Skybox.hpp"

// the size of how many floats a vertex use to describe all its attributes
const unsigned int attr_size = 5;

class SDLGraphicsProgram {
public:
    // Constructor
    SDLGraphicsProgram(int w, int h, float sensitivity, float moveSpeed);
    // Destructor
    ~SDLGraphicsProgram();
    // Update Objects
    void Update();
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

    // Camera properties:
    Camera* camera;

    // the speed at which the camera moves
    float moveSpeed;
    // mouse sensitivity
    float mouseSensitivity;

    // Mouse position properties
    int mousePosX;
    int mousePosY;

    // The ID of the OpenGL Program
    unsigned int program;

    // List of Cubes
    std::vector<Cube*> cubes;

    Skybox * skybox;
};


#endif