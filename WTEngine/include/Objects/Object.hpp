#ifndef OBJECT_HPP
#define OBJECT_HPP

// C++ libraries
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb/stb_image.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"

// Standard stuff
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

struct Vertex {
	// coordinates of the vertex
	float x, y, z;

	Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
};

struct TexCoord {
	// texture mapping
	float s, t;

	TexCoord(float _s, float _t) : s(_s), t(_t) { }
};

struct TexturedVertex {
	// coordinates of the vertex
	float x, y, z;
	// texture mapping
	float s, t;

	TexturedVertex(float _x, float _y, float _z, float _s, float _t) : x(_x), y(_y), z(_z), s(_s), t(_t) { }

	// Tests if two VertexData are equal
	bool operator== (const TexturedVertex rhs) const {
		if ((x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (s == rhs.s) && (t == rhs.t)) {
			return true;
		}
		return false;
	}

	bool operator<(const TexturedVertex rhs) const {
		return memcmp((void*)this, (void*)&rhs, sizeof(TexturedVertex)) > 0;
	};
};

class Object {
public:
	// Constructor
	Object(std::string _id, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _offset, std::string modelLoc, std::string textureLoc);
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
protected:
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