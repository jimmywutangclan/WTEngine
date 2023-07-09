#include "Objects/Object.hpp"

Object::Object(std::string _id, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, glm::vec3 _offset, std::string modelLoc, std::string textureLoc) {
	if (modelLoc == "") {
		vertexArray = {
			// Back cube
			// First Triangle
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // bottom right
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, // top right 
			// Second Triangle
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // top left
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
			-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // top right

			// Front cube
			// Third Triangle
			-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // bottom left
			0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // bottom right
			0.5f,  0.5f, 0.5f, 1.0f, 0.0f, // top right 
			// Fourth Triangle
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // top left
			-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // bottom left
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top right

			// Side left cube
			// First Triangle
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
			-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // bottom right
			-0.5f,  0.5f, 0.5f, 1.0f, 0.0f, // top right 
			// Second Triangle
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // top left
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top right

			// Side right cube
			// First Triangle
			0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // bottom left
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // bottom right
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // top right 
			// Second Triangle
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // top left
			0.5f, -0.5f, 0.5f, 0.0f, 1.0f, // bottom left
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // top right

			// top cube
			// First Triangle
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, //bottom left
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // bottom right
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // top right
			// Second triangle
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // top left
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, //bottom left
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // top right

			// bottom cube
			// First Triangle
			0.5f, -0.5f, 0.5f, 0.0f, 1.0f, //bottom left
			-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, // bottom right
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // top right
			// Second triangle
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // top left
			0.5f, -0.5f, 0.5f, 0.0f, 1.0f, //bottom left
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // top right
		};

		indexArray = {
			// back cube
			0,1,2,
			3,4,5,
			// front cube
			6,7,8,
			9,10,11,
			// side left
			12,13,14,
			15,16,17,
			// side right
			18,19,20,
			21,22,23,
			// top cube
			24,25,26,
			27,28,29,
			// bottom cube
			30,31,32,
			33,34,35
		};
	}
	else {
		std::ifstream infile;
		infile.open(modelLoc);
		std::string token;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;

		std::map<Vertex, int> vertexIndexMap;

		int uniqueVerticesCount = 0;

		while (infile >> token) {
			// Recognizes v, vt and f flags(For vertex, vertex texture coord, and which vertices are in a triangle(aka index array))
			if (token[0] == 'v') {
				if (token[1] == '\0') {
					infile >> token;
					float x = std::stof(token);
					infile >> token;
					float y = std::stof(token);
					infile >> token;
					float z = std::stof(token);
					glm::vec3 v(x, y, z);
					vertices.push_back(v);
				}
				else if (token[1] == 'n') {
					infile >> token;
					float x = std::stof(token);
					infile >> token;
					float y = std::stof(token);
					infile >> token;
					float z = std::stof(token);
					glm::vec3 v(x, y, z);
					normals.push_back(v);
				}
				else if (token[1] == 't') {
					infile >> token;
					float s = std::stof(token);
					infile >> token;
					float t = std::stof(token);
					glm::vec2 tex(s, t);
					texCoords.push_back(tex);
				}
			}
			else if (token[0] == 'f') {
				for (int i = 0; i < 3; i++) {
					infile >> token;

					char* vCstr;
					char* vtCstr;
					char* vnCstr;
					char* tokenizerState;

					int vIdx = -1;
					int vtIdx = -1;
					int vnIdx = -1;

					char* face_cstr = new char[token.size() + 1];
					rsize_t maxSize = sizeof face_cstr;
					memcpy(face_cstr, token.c_str(), token.size() + 1);

					vCstr = strtok_s(face_cstr, "/", &tokenizerState);
					vtCstr = strtok_s(NULL, "/", &tokenizerState);
					vnCstr = strtok_s(NULL, "/", &tokenizerState);

					vIdx = std::stoi(vCstr) - 1;
					vtIdx = std::stoi(vtCstr) - 1;
					vnIdx = std::stoi(vnCstr) - 1;

					glm::vec3 currVertex = vertices[vIdx];
					glm::vec3 currNormal = normals[vnIdx];
					glm::vec2 currTexCoord = texCoords[vtIdx];

					Vertex curr;
					curr.pos = currVertex;
					curr.normal = currNormal;
					curr.texcoords = currTexCoord;

					if (vertexIndexMap.find(curr) == vertexIndexMap.end()) {
						vertexIndexMap.insert(std::make_pair(curr, vertexIndexMap.size()));
						vertexArray.push_back(currVertex.x);
						vertexArray.push_back(currVertex.y);
						vertexArray.push_back(currVertex.z);
						vertexArray.push_back(currNormal.x);
						vertexArray.push_back(currNormal.y);
						vertexArray.push_back(currNormal.z);
						vertexArray.push_back(currTexCoord.x);
						vertexArray.push_back(currTexCoord.y);
					}
					int vertexIndex = vertexIndexMap.find(curr)->second;
					indexArray.push_back(vertexIndex);
				}
			}
		}
	}

	// Generate all buffers first
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO buffer 
	glBindVertexArray(VAO);
	// Set up VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexArray.size(), &vertexArray[0], GL_STATIC_DRAW);
	// Set up EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexArray.size(), &indexArray[0], GL_STATIC_DRAW);
	// Set up vertex attribute pointer within VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); // attribute 0(position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))); // attribute 1(normal)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float))); // attribute 2(texture)
	glEnableVertexAttribArray(2);

	// Set up texture 1
	int width, height, nrChannels;
	unsigned char* textureData = stbi_load(textureLoc.c_str(), &width, &height, &nrChannels, 0);
	if (!textureData) {
		std::cout << "Texture loading error" << std::endl;
		exit(EXIT_FAILURE);
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData);

	// Set transforms and objec id
	position = _position;
	rotation = _rotation;
	scale = _scale;
	offset = _offset;
	id = _id;

	// Set up Parent object pointer
	parent = nullptr;
	// Set up world model matrix
	worldModelMatrix = glm::mat4(1.0f);

	// Calculate the world model matrix
	CalculateWorldModelMatrix();
}

Object::~Object() {

}

void Object::Update() {
	for (Object* child : children) {
		child->Update();
	}
}

void Object::Render(glm::mat4 view, glm::mat4 proj, unsigned int program) {
	// pass the model matrix into the shaders
	unsigned int modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(worldModelMatrix));

	// retrieve the matrix uniform locations
	unsigned int viewLoc = glGetUniformLocation(program, "view");
	unsigned int projLoc = glGetUniformLocation(program, "projection");
	// pass them to the shaders 
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	// Set up uniform variable for the texture
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "texture_diffuse1"), 0); // Set up uniform variable "texture_diffuse1" to use the 0th texture


	// Activate and bind texture, VBO and EBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Using the existing VBO, VAO, and EBO here, draw another object in the new world space updated earlier
	glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	for (Object* child : children) {
		child->Render(view, proj, program);
	}
}

// Transform getters and setters
glm::vec3 Object::GetPosition() {
	return glm::vec3(position.x, position.y, position.z);
}

glm::vec3 Object::GetRotation() {
	return glm::vec3(rotation.x, rotation.y, rotation.z);
}

glm::vec3 Object::GetScale() {
	return glm::vec3(scale.x, scale.y, scale.z);
}

glm::vec3 Object::GetOffset() {
	return glm::vec3(offset.x, offset.y, offset.z);
}

void Object::SetPosition(glm::vec3 _position) {
	position = _position;
	CalculateWorldModelMatrix();
}

void Object::SetRotation(glm::vec3 _rotation) {
	rotation = _rotation;
	CalculateWorldModelMatrix();
}

void Object::SetScale(glm::vec3 _scale) {
	scale = _scale;
	CalculateWorldModelMatrix();
}

void Object::SetOffset(glm::vec3 _offset) {
	offset = _offset;
	CalculateWorldModelMatrix();
}

// Adding child Object
void Object::AddChild(Object* child) {
	children.push_back(child);
	child->parent = this;
}

// Getting a child with a specific id
Object * Object::GetChild(std::string childId) {
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->id == childId) {
			return children[i];
		}
	}

	return nullptr;
}

// Calculating world model matrix, calls children too
void Object::CalculateWorldModelMatrix() {
	if (parent == nullptr) {
		worldModelMatrix = glm::mat4(1.0f);
	}
	else {
		worldModelMatrix = glm::mat4(parent->worldModelMatrix);
	}

	glm::quat rotationQuat = glm::quat(rotation);
	glm::mat4 rotationMatrix = glm::mat4_cast(rotationQuat);

	worldModelMatrix = glm::translate(worldModelMatrix, position);
	worldModelMatrix *= rotationMatrix;
	worldModelMatrix = glm::scale(worldModelMatrix, scale);
	worldModelMatrix = glm::translate(worldModelMatrix, offset);

	for (Object* child : children) {
		child->CalculateWorldModelMatrix();
	}
}