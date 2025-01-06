#pragma once

#include <SDL.h>
#include <vector>

#include "vector2.h"

class Bird
{
public:
	Bird(SDL_Rect rect, SDL_Color color, Vector2 velocity);

	Vector2 getPosition();
	Vector2 getVelocity();

	void render(SDL_Renderer* renderer);
	void update(std::vector<Bird*> flock);
private:
	std::vector<Bird*> getNeighbors(std::vector<Bird*> flock);

	void alignTo(std::vector<Bird*> neighbors, float scale);
	void separateFrom(std::vector<Bird*> neighbors, float scale);
	void cohereWith(std::vector<Bird*> neighbors, float scale);
private:
	SDL_Rect m_Rect;
	SDL_Color m_Color;
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
};