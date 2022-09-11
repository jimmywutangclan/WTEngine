#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "SDLGraphicsProgram.hpp"

int main(int argc, char * argv[]) {
	SDLGraphicsProgram program = SDLGraphicsProgram(600, 600);
	program.Loop();

	return 0;
}