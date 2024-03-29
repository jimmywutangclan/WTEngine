#ifndef SKYBOX_HPP
#define SKYBOX_HPP

// C++ libraries
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb/stb_image.h"
#include "glm/gtc/type_ptr.hpp"

// Standard stuff
#include <vector>
#include <iostream>
#include <string>

// In house stuff
#include <Objects/Object.hpp>

class Skybox {
public:
	Skybox(float viewingDist, std::string textureLoc);

	~Skybox();

	void Render(glm::mat4 view, glm::mat4 proj, unsigned int program);

	// Transformation for the object
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
private:
	// How many attributes in the VBO and VAO?
	const unsigned int attrs_size = 5;

	// Vertex/Index array
	std::vector<float> vertexArray;
	std::vector<unsigned int> indexArray;

	// VBO/VAO/EBO for the cube
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// Texture buffer for the Cube
	unsigned int texture;
};

#endif