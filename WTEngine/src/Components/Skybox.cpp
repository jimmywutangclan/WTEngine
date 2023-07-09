#include "Components/Skybox.hpp"

Skybox::Skybox(float viewingDist, std::string textureLoc) {
	vertexArray = {
		// -z cube
		// First Triangle
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.66666f, // bottom left inside
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66666f, // bottom right inside
		0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.33334f, // top right inside 
		// Second Triangle
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.33334f, // top left inside
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.66666f, // bottom left inside
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.33334f, // top right inside

		// +x cube
		// First triangle
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66666f, // bottom left inside
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.66666f, // bottom right inside
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.33334f, // top right inside
		// Second triangle
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.33334f, // top left inside
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66666f, // bottom left inside
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.33334f, // top right inside

		// +z cube
		// First triangle
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.66666f, // bottom left inside
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.66666f, // bottom right inside
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.33334f, // top right inside
		// Second Triangle
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.33334f, // top left inside
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.75f, 0.66666f, // bottom left inside
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.33334f, // top right inside

		// -x cube
		// First triangle
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.66666f, // bottom left inside
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.66666f, // bottom right inside
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.33334f, // top right inside
		// Second triangle
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.33334f, // top left inside
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.66666f, // bottom left inside
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.33334f, // top right inside

		// +y cube
		// First triangle
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.33333f, // bottom left inside
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.33333f, // bottom right inside
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, // top right inside
		// Second triangle
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.0f, // top left inside
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.33333f, // bottom left inside
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, // top right inside

		// -y cube
		// First triangle
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, // bottom left inside
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, // bottom right inside
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66666f, // top right inside
		// Second triangle
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.66666f, // top left inside
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 1.0f, // bottom left inside
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.66666f, // top right inside
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float))); // attribute 1(normal mapping)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float))); // attribute 2(texture mapping)
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

	position = glm::vec3(0,0,0);
}

Skybox::~Skybox() {

}

void Skybox::Render(glm::mat4 view, glm::mat4 proj, unsigned int program) {
	// Starting from identity matrix, set the quad's position relative to the world origin, rotate, and then scale the model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(100,100,100));

	// pass the model matrix into the shaders
	unsigned int modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// retrieve the matrix uniform locations
	unsigned int viewLoc = glGetUniformLocation(program, "view");
	unsigned int projLoc = glGetUniformLocation(program, "projection");
	// pass them to the shaders 
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	// Set up uniform variable for the texture
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "texture1"), 0); // Set up uniform variable "texture1" to use the 0th texture


	// Activate and bind texture, VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Using the existing VBO, VAO, and EBO here, draw another cube in the new world space updated earlier
	glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

}