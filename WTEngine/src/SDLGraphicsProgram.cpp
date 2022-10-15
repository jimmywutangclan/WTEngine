#include "SDLGraphicsProgram.hpp"

// Constructor
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h, float sensitivity, float speed) {
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

	// Set up Camera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, -90.0f, width, height, 100);

	// Set up mouse and movement input settings
	mousePosX = width / 2;
	mousePosY = height / 2;
	moveSpeed = speed;
	mouseSensitivity = sensitivity;

	// Add cubes to the world
	Cube * cringe_cube = new Cube("cringe", glm::vec3(4.0f, 0.0f, -3.0f), glm::vec3(0, 90, 0), glm::vec3(1.3f, 1.3f, 1.3f), glm::vec3(0, 0, 0), "./resources/lose_subscriber.png");
	Cube * new_cube = new Cube("troll", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), "./resources/fortnit.jpg");
	Cube * new_cube2 = new Cube("troll2", glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0, 0, 0), "./resources/fortnit.jpg");
	cubes.push_back(new_cube);
	//cubes.push_back(cringe_cube);
	new_cube->AddChild(cringe_cube);
	cringe_cube->AddChild(new_cube2);

	skybox = new Skybox(camera->viewingDist, "./resources/hqskybox.jpg");

	std::cout << "Game Objects created" << std::endl;
}

// Destructor
SDLGraphicsProgram::~SDLGraphicsProgram() {
	// delete the memory address containing the window
	SDL_DestroyWindow(window);

	SDL_Quit();
}

// For each tick within the Loop, update the Game Objects
void SDLGraphicsProgram::Update() {
	for (int i = 0; i < cubes.size(); i++) {
		if (cubes[i]->id == "troll") {
			cubes[i]->SetRotation(cubes[i]->GetRotation() + glm::vec3(0, 0.1f, 0));
			cubes[i]->GetChild("cringe")->SetRotation(cubes[i]->GetChild("cringe")->GetRotation() + glm::vec3(0, 0.1f, 0));
		}
	}
}

// For each tick within the Loop, call render to generate image
void SDLGraphicsProgram::Render() {
	// Just render background
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Clear color buffer and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw skybox
	skybox->Render(camera->getViewMatrix(), camera->getProjectionMatrix(), program);

	// Activate program and draw the shapes
	for (Cube * c : cubes) {
		c->Render(camera->getViewMatrix(), camera->getProjectionMatrix(), program);
	}


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
			else if (e.type == SDL_MOUSEMOTION) {
				// capture cursor location update for the mouse
				int newMousePosX = e.motion.x;
				int newMousePosY = e.motion.y;

				float xDiff = newMousePosX - mousePosX;
				float yDiff = newMousePosY - mousePosY;
				xDiff *= mouseSensitivity;
				yDiff *= mouseSensitivity;

				mousePosX = newMousePosX;
				mousePosY = newMousePosY;

				camera->rotateDir(yDiff, -xDiff, 0);
			}
			else if (e.type = SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_q:
						quit = true;
						break;
					case SDLK_w:
						camera->moveRelativeToForward(moveSpeed, 0, 0);
						break;
					case SDLK_s:
						camera->moveRelativeToForward(-moveSpeed, 0, 0);
						break;
					case SDLK_a:
						camera->moveRelativeToForward(0, -moveSpeed, 0);
						break;
					case SDLK_d:
						camera->moveRelativeToForward(0, moveSpeed, 0);
						break;
				}
			}
		}

		// Update position of the skybox
		skybox->position = camera->position;

		Update();
		Render();
	}

	std::cout << "That's all folks!" << std::endl;
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