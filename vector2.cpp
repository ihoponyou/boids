#include <cmath>
#include <iostream>

#include "vector2.h"

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
	
}

Vector2& Vector2::operator+(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2& Vector2::operator-(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2& Vector2::operator*(const double& d)
{
	this->x *= d;
	this->y *= d;
	return *this;
}

Vector2& Vector2::operator/(const double& d)
{
	if (d == 0)
	{
		std::cout << this;
		return *this;
	}
	this->x /= d;
	this->y /= d;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	return *this + v;
}

Vector2& Vector2::operator/=(const double& d)
{
	return *this / d;
}

double Vector2::magnitude()
{
	return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

Vector2 Vector2::normalized()
{
	double length = magnitude();
	return Vector2(this->x/length, this->y/length);
}
