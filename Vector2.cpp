#include "Vector2.h"
#include <math.h>

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}

bool Vector2::operator==(const Vector2& vec2) const {
	return x == vec2.x && y == vec2.y;
}
bool Vector2::operator!=(const Vector2& vec2) const {
	return !(x == vec2.x && y == vec2.y);
}

const Vector2 Vector2::operator+(const Vector2& vec2) const {
	return Vector2(x + vec2.x, y + vec2.y);
}
const Vector2 Vector2::operator-(const Vector2& vec2) const {
	return Vector2(x - vec2.x, y - vec2.y);
}
const Vector2 Vector2::operator*(const float& var) const {
	return Vector2(x * var, y * var);
}

void Vector2::operator+=(const Vector2& vec2) {
	x = x + vec2.x;
	y = y + vec2.y;
}
void Vector2::operator-=(const Vector2& vec2) {
	x = x - vec2.x;
	y = y - vec2.y;
}
void Vector2::operator*=(const float& var) {
	x = x * var;
	y = y * var;
}

const float Vector2::Lenght() const {
	float temp = (x * x) + (y * y);
	return (float)sqrt(temp);
}
const Vector2 Vector2::Normalize() const {
	float lenght = Lenght();
	return Vector2(x / lenght, y / lenght);
}