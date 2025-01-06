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
	
	SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRect(renderer, &m_Rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	int centerXPos{ m_Rect.x + m_Rect.w / 2 };
	int centerYPos{ m_Rect.y + m_Rect.h / 2 };
	SDL_RenderDrawLine(renderer,
		centerXPos,
		centerYPos,
		centerXPos + m_Velocity.x * 10,
		centerYPos + m_Velocity.y * 10
	);

	SDL_SetRenderDrawColor(renderer, oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

void Bird::update()
{
	m_Rect.x += m_Velocity.x;
	m_Rect.y += m_Velocity.y;

	// right boundary
	if (m_Rect.x > SCREEN_SIDE_LENGTH)
	{
		m_Rect.x = -m_Rect.w;
	}
	// left boundary
	else if (m_Rect.x < -m_Rect.w)
	{
		m_Rect.x = SCREEN_SIDE_LENGTH;
	}
	// bottom boundary
	if (abs(m_Rect.y) > SCREEN_SIDE_LENGTH)
	{
		m_Rect.y = -m_Rect.h;
	}
	// top boundary
	else if (m_Rect.y < -m_Rect.h)
	{
		m_Rect.y = SCREEN_SIDE_LENGTH;
	}
}
