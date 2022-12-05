#pragma once

#include <ostream>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& v);
	virtual ~Vector2() {}

	// basic functions
	float dist(const Vector2& v) const;
	bool empty() { return (x == 0 && y == 0) ? true : false; }

	static Vector2 Lerp(Vector2 v1, Vector2 v2, float t);

	// operators
	Vector2& operator=(const Vector2& v);
	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator-();
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);

	Vector2& operator*(const Vector2& v);
	Vector2& operator*(float scaler);

	Vector2& operator/(const Vector2& v);
	Vector2& operator/(float scaler);
	
	bool operator==(const Vector2& v) const;

	// data - public
	float     x{ 0 }, y{ 0 };
};

// additional operators for arithmetic and stream operations
Vector2 operator+(const Vector2& lv, const Vector2& rv);
Vector2 operator-(const Vector2& lv, const Vector2& rv);
std::ostream& operator<<(std::ostream& out, const Vector2& v);