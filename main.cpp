#include <SDL.h>
#include <vector>
#include <random>
#include "bird.h"

#define TITLE "boids"
#define SCREEN_SIDE_LENGTH 700
#define INITIAL_BIRDS 10
#define BIRD_WIDTH 10
#define BIRD_HEIGHT 10
#define FRAMES_PER_SECOND 60
constexpr auto OPTIMAL_FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

std::random_device randomDevice;
std::mt19937 generator( randomDevice() );

// returns an int in [0, max]
int getRandomInt(int max)
{
	return generator() % max;
}

int main(int argc, char* argv[])
{
	SDL_Window* window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIDE_LENGTH, SCREEN_SIDE_LENGTH, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// generate birds
	std::vector<Bird*> birds{};
	for (int i = 0; i < INITIAL_BIRDS; i++)
	{
		SDL_Rect rect{ getRandomInt(SCREEN_SIDE_LENGTH) , getRandomInt(SCREEN_SIDE_LENGTH) , BIRD_WIDTH, BIRD_HEIGHT};
		SDL_Color color{ 255, 0, 0, 255 };
		Vector2 velocity{ 1, 0 };

		Bird* newBird = new Bird(rect, color, velocity);
		birds.push_back(newBird);
	}

	Uint32 frameStart;
	int frameTime;
	bool running = true;
	while (running)
	{
		frameStart = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		
		// draw birds
		for (int i{ 0 }; i < birds.size(); i++)
		{
			birds[i]->update();
			birds[i]->render(renderer);
		}
		
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;
		if (OPTIMAL_FRAME_DELAY > frameTime)
		{
			SDL_Delay(OPTIMAL_FRAME_DELAY - frameTime);
		}
	}

	SDL_Quit();
	return 0;
}