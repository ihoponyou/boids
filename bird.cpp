#include <iostream>
#include "bird.h"
#include "config.h"

Bird::Bird(SDL_Rect rect, SDL_Color color, Vector2 velocity)
{
	//printf("created bird {x=%d, y=%d}, {w=%d, h=%d}, {R=%d, G=%d, B=%d}\n", rect.x, rect.y, rect.w, rect.h, color.r, color.g, color.b);
	m_Rect = rect;
	m_Color = color;
	m_Velocity = velocity;
}

void Bird::render(SDL_Renderer* renderer)
{
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(renderer, &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
	
	// draw bird
	SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRect(renderer, &m_Rect);

	// draw velocity visualizer
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	int centerXPos{ m_Rect.x + m_Rect.w / 2 };
	int centerYPos{ m_Rect.y + m_Rect.h / 2 };
	SDL_RenderDrawLine(renderer,
		centerXPos,
		centerYPos,
		centerXPos + m_Velocity.x * 5,
		centerYPos + m_Velocity.y * 5
	);

	// reset draw color
	SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

void Bird::update(std::vector<Bird*> flock)
{
	std::vector<Bird*> neighbors{ getNeighbors(flock) };
	separateFrom(neighbors, SEPARATION_FACTOR);
	alignTo(neighbors, ALIGNMENT_FACTOR);
	cohereWith(neighbors, COHESION_FACTOR);

	if (m_Acceleration.magnitude() > MAX_ACCELERATION_FORCE)
		m_Acceleration = m_Acceleration.normalized() * MAX_ACCELERATION_FORCE;
	
	m_Velocity.x += m_Acceleration.x;
	m_Velocity.y += m_Acceleration.y;

	if (m_Velocity.magnitude() > MAX_SPEED)
		m_Velocity = m_Velocity.normalized() * MAX_SPEED;

	m_Rect.x += m_Velocity.x;
	m_Rect.y += m_Velocity.y;

	// teleport if outside of screen bounds
	if (m_Rect.x > SCREEN_SIDE_LENGTH)
	{
		m_Rect.x = -m_Rect.w;
	}
	else if (m_Rect.x < -m_Rect.w)
	{
		m_Rect.x = SCREEN_SIDE_LENGTH;
	}
	if (m_Rect.y > SCREEN_SIDE_LENGTH)
	{
		m_Rect.y = -m_Rect.h;
	}
	else if (m_Rect.y < -m_Rect.h)
	{
		m_Rect.y = SCREEN_SIDE_LENGTH;
	}
}

Vector2 Bird::getPosition()
{
	return Vector2( m_Rect.x, m_Rect.y );
}

Vector2 Bird::getVelocity()
{
	return m_Velocity;
}

std::vector<Bird*> Bird::getNeighbors(std::vector<Bird*> flock)
{
	// TODO: use quadtree
	// TODO: add abillity to "see" through the boundaries
	std::vector<Bird*> neighbors{};
	for (int i = 0; i < flock.size(); i++)
	{
		Bird* otherBird = flock[i];
		if (this == otherBird)
			continue;

		if ((this->getPosition()-otherBird->getPosition()).magnitude() > NEIGHBOR_RADIUS)
			continue;

		neighbors.push_back(otherBird);
	}

	return neighbors;
}

// steer to avoid crowding local flockmates
void Bird::separateFrom(std::vector<Bird*> neighbors, float factor)
{
	if (neighbors.size() < 1)
		return;

	Vector2 totalAcceleration{};
	for (auto bird : neighbors)
	{
		Vector2 fromBirdToThis = this->getPosition() - bird->getPosition();
		if (fromBirdToThis.magnitude() == 0)
			continue;
		totalAcceleration += fromBirdToThis;
	}
	totalAcceleration /= neighbors.size();

	m_Acceleration += totalAcceleration * factor;
}

// steer towards the average heading of local flockmates
void Bird::alignTo(std::vector<Bird*> neighbors, float factor)
{
	if (neighbors.size() < 1)
		return;

	Vector2 averageDirection{};
	for (auto bird : neighbors)
		averageDirection += bird->getVelocity();
	averageDirection /= neighbors.size();

	m_Acceleration += (averageDirection - m_Velocity) * factor;
}

// steer to move towards the average position (center of mass) of local flockmates
void Bird::cohereWith(std::vector<Bird*> neighbors, float factor)
{
	if (neighbors.size() < 1)
		return;

	Vector2 averagePosition{};
	for (auto bird : neighbors)
		averagePosition += bird->getPosition();
	averagePosition /= neighbors.size();

	m_Acceleration += (averagePosition - this->getPosition()) * factor;
}
