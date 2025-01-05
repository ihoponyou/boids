#include <SDL.h>

int main(int argc, char* argv[])
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "title", "message", NULL);
	return 0;
}