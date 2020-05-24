#pragma once

class Vector2 {
public:
	float x, y;

	Vector2();
	Vector2(float, float);

	bool operator==(const Vector2&) const;
	bool operator!=(const Vector2&) const;
	const Vector2 operator+(const Vector2&) const;
	const Vector2 operator-(const Vector2&) const;
	const Vector2 operator*(const float&) const;
	void operator+=(const Vector2&);
	void operator-=(const Vector2&);
	void operator*=(const float&);

	const float Lenght() const;
	const Vector2 Normalize() const;
};

