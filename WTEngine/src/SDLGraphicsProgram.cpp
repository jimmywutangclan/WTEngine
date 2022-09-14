#include "SDLGraphicsProgram.hpp"

// Constructor
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) {
	width = w;
	height = h;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Init error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Use OpenGL 3.3 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// We want to request a double buffer for smooth updating.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create window
	window = SDL_CreateWindow("WTEng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Window error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create OpenGL Graphics Context within our window
	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) {
		std::cout << "OpenGL Context error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Initialize GLAD GL library
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cout << "GLAD initialization error" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set up OpenGL Shaders
	program = SetupShaders();
	if (program == GL_FALSE) {
		std::cout << "Shaders error" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Setup success" << std::endl;

	// Set up base triangle 2 attributes, position/texture mapping)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attr_size * sizeof(float), (void*)0); // attribute 0(position)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, attr_size * sizeof(float), (void*)(3 * sizeof(float))); // attribute 1(texture mapping)
	glEnableVertexAttribArray(1);
	
	// Set up texture 1
	int width, height, nrChannels;
	unsigned char* textureData = stbi_load("./resources/lose_subscriber.png", &width, &height, &nrChannels, 0);
	if (!textureData) {
		std::cout << "Texture loading error" << std::endl;
		exit(EXIT_FAILURE);
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData);

	// Set up uniform variable for the texture
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "texture1"), 0); // Set up uniform variable "texture1" to use the 0th texture

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	std::cout << "Quad creation success" << std::endl;

	curr_angle = 0.0f;
}

// Destructor
SDLGraphicsProgram::~SDLGraphicsProgram() {
	// delete the memory address containing the window
	SDL_DestroyWindow(window);

	SDL_Quit();
}

// Called by Render each time, to draw the cube at a specific position, rotate it, and update uniform transformation matrices
void SDLGraphicsProgram::UpdateCube(float x, float y, float z) {
	// Starting from identity matrix, set the quad's position relative to the world origin, rotate, and then scale the model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x,y,z)); // Rotate matrix by 90 degrees on the z-axis
	model = glm::rotate(model, glm::radians(curr_angle), glm::vec3(1.0f, 1.0f, 1.0f)); // Rotate matrix by 90 degrees on specified axes
	model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f)); // Scale all axes by 0.6x
	unsigned int modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// Increment the angle after every tick
	curr_angle += 0.25f;
	if (curr_angle >= 360.0f) {
		curr_angle = 0;
	}


	// This is the logic for view and projection(above transform is for model)
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // The desired position for the view is reversed, to apply onto the model
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int viewLoc = glGetUniformLocation(program, "view");
	unsigned int projLoc = glGetUniformLocation(program, "projection");
	// pass them to the shaders 
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

// For each tick within the Loop, call render to generate image
void SDLGraphicsProgram::Render() {
	// Just render background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Clear color buffer and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateCube(-0.2, 0.2, 0.3);

	// Activate program and draw the shapes
	glUseProgram(program);
	glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, 0);

	// Update the cube world space to be a new value
	UpdateCube(0.7, 0.7, -0.3);
	// Using the existing VBO, VAO and EBO, draw another cube in the new world space updated earlier
	glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_INT, 0);


	SDL_GL_SwapWindow(window);
}

// Indefinitely running main loop
void SDLGraphicsProgram::Loop() {
	//Update screen of our specified window
	bool quit = false;
	
	// Event handler
	SDL_Event e;

	while (!quit) {
		// SDL Accept input
		while (SDL_PollEvent(&e) != 0) {
			// Quit application
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type = SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}

		Render();

	}
}




















// OpenGL Setup logic:

unsigned int SDLGraphicsProgram::SetupShaders() {
	// Load Shaders from GLSL file
	std::string vertexShaderCode = LoadShader("./shaders/vert.glsl");
	std::string fragmentShaderCode = LoadShader("./shaders/frag.glsl");

	const char* vertexShaderCstr = vertexShaderCode.c_str();
	const char* fragmentShaderCstr = fragmentShaderCode.c_str();

	// Compile and bind vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCstr, NULL);
	glCompileShader(vertexShader);

	// Compile and bind fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCstr, NULL);
	glCompileShader(fragmentShader);

	// Check if shaders compiled properly
	int vertexResult;
	int fragResult;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexResult);
	if (vertexResult == GL_FALSE) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader compilation error" << std::endl;
		std::cout << infoLog << std::endl;
		glDeleteShader(vertexShader);
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragResult);
	if (fragResult == GL_FALSE) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment shader compilation error" << std::endl;
		std::cout << infoLog << std::endl;
		glDeleteShader(fragmentShader);
	}

	// If compilation failed, early exit
	if (vertexResult == GL_FALSE || fragResult == GL_FALSE) {
		return GL_FALSE;
	}

	// Create a shader program and link shaders to it
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int programResult;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programResult);
	if (programResult == GL_FALSE) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Shader program linking error" << std::endl;
		std::cout << infoLog << std::endl;
		glDeleteProgram(shaderProgram);
	}

	// If program failed to link, early exit
	if (programResult == GL_FALSE) {
		return GL_FALSE;
	}
	
	// Clean up and delete shaders, no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return shaderProgram;

}

std::string SDLGraphicsProgram::LoadShader(std::string dir) {
	std::string result;
	std::string line;
	std::ifstream curr(dir.c_str());

	if (curr.is_open()) {
		while (getline(curr, line)) {
			result += line + "\n";
		}
	}

	curr.close();
	return result;
}