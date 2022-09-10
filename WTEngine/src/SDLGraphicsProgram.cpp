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
	window = SDL_CreateWindow("WTEng", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
	if (!SetupShaders()) {
		std::cout << "Shaders error" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Setup success" << std::endl;

	// Set up base vertex array
	vertexArray = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

}

// Destructor
SDLGraphicsProgram::~SDLGraphicsProgram() {
	// delete the memory address containing the window
	SDL_DestroyWindow(window);

	SDL_Quit();
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

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Update screen of our specified window
		SDL_GL_SwapWindow(window);
	}
}




















// OpenGL Setup logic:

bool SDLGraphicsProgram::SetupShaders() {
	std::string vertexShaderCode = LoadShader("./shaders/vert.glsl");
	std::string fragmentShaderCode = LoadShader("./shaders/frag.glsl");

	const char* vertexShaderCstr = vertexShaderCode.c_str();
	const char* fragmentShaderCstr = fragmentShaderCode.c_str();

	// Compile and bind vertex shader first
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
		return false;
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
		return false;
	}
	
	// Clean up and delete shaders, no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return true;

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