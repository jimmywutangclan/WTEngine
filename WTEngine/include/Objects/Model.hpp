#ifndef MODEL_HPP
#define MODEL_HPP

// C++ libraries
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb/stb_image.h"
#include "glm/gtc/type_ptr.hpp"

// Standard stuff
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

// In-house code
#include "Objects/Object.hpp"

class Model : Object {
public:
	// Constructor
	Model(std::string _id, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _offset, std::string modelLoc, std::string textureLoc);
	// Destructor
	~Model();
};

#endif