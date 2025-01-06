#pragma once

class Vector2
{
public:
	double x, y;
	Vector2(double x = 0, double y = 0);

	Vector2& operator+(const Vector2& v);
	Vector2& operator-(const Vector2& v);
	Vector2& operator*(const double& d);
	Vector2& operator/(const double& d);

	Vector2& operator+=(const Vector2& v);
	Vector2& operator/=(const double& v);

	double magnitude();
	Vector2 normalized();
};