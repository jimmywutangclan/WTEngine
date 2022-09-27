#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "SDLGraphicsProgram.hpp"

int main(int argc, char * argv[]) {
	SDLGraphicsProgram program = SDLGraphicsProgram(1920, 1080, -0.2f, 0.05f);
	program.Loop();

	return 0;
}