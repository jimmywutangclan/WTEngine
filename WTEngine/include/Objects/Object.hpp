#ifndef CUBE_HPP
#define CUBE_HPP

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

class Object {
public:
	// Constructor
	Object(std::string _id, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _offset, std::string textureLoc);
	// Destructor
	~Object();

	void Update();

	void Render(glm::mat4 view, glm::mat4 proj, unsigned int program);

	// Getters for transformation(gets copy)
	glm::vec3 GetPosition();

	glm::vec3 GetRotation();

	glm::vec3 GetScale();

	glm::vec3 GetOffset();

	// Setters for transformation(updates world matrix)
	void SetPosition(glm::vec3 _position);

	void SetRotation(glm::vec3 _rotation);

	void SetScale(glm::vec3 _scale);

	void SetOffset(glm::vec3 _offset);

	// Add Child Cube
	void AddChild(Object* child);

	// Get Child of a specific id
	Object* GetChild(std::string childId);

	// ID of the cube
	std::string id;
private:
	// Calculate the World Model Matrix
	void CalculateWorldModelMatrix();

	// Transformation for the object
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 offset; // offset of the object from its center(position)

	// How many attributes in the VBO and VAO?
	const unsigned int attrs_size = 5;

	// Vertex/Index array
	std::vector<float> vertexArray;
	std::vector<unsigned int> indexArray;

	// VBO/VAO/EBO for the object
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// Texture buffer for the Object
	unsigned int texture;

	// Transform
	// Matrix of the parent transforms cumulatively combined together
	glm::mat4 worldModelMatrix;

	// Parent Object
	Object* parent;
	// List of children
	std::vector<Object*> children;
};

#endif