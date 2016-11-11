#include "SDL.h"

int main(int argc, char* argv[])
{
	// Start up:
	SDL_Init(SDL_INIT_EVERYTHING);

	// Clean up:
	SDL_Quit();

	return 0;
}