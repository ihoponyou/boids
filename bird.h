#pragma once

#include <SDL.h>
#include "vector2.h"

class Bird
{
public:
	Bird(SDL_Rect rect, SDL_Color color, Vector2 velocity);

	void render(SDL_Renderer*);
	void update();
private:
	SDL_Rect m_Rect;
	SDL_Color m_Color;
	Vector2 m_Velocity;
};