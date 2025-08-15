#pragma once
#include "pch.h" 
#include <cmath>
#include <algorithm> 

class Vector2
{
public:
	Vector2() : x(), y() {}
	Vector2(float tx, float ty) : x(tx), y(ty) {}

	const float& get_xpos() const { return x; }
	const float& get_ypos() const { return y; }

	void set_transform(const float& sx, const float& sy)
	{
		x = sx;
		y = sy;

	}
	Vector2 operator+ (const Vector2& other) const
	{
		return Vector2(this->x + other.x, this->y + other.y);
	}


	Vector2 operator- (const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator* (const float& other) const
	{
		return Vector2(x * other, y * other);
	}

	Vector2 operator/ (const float& other) const
	{
		return Vector2(x / other, y / other);
	}

	void operator*= (const float& other)
	{
		x *= other;
		y *= other;
	}

	void operator+= (const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-= (const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}
	bool operator==(const Vector2& rhs) const
	{
		constexpr float eps = std::numeric_limits<float>::epsilon() * 100;
		return std::fabs(x - rhs.x) < eps && std::fabs(y - rhs.y) < eps;
	}
	bool operator!= (const Vector2& other) const
	{
		return !(*this == other);
	}

	float operator[] (size_t idx) const
	{
		switch (idx)
		{
		case 0:
			return x;
		case 1:
			return y;
		default:
			throw std::out_of_range("원소 개수 초과");
			break;
		}
	}

	

	friend std::ostream& operator << (std::ostream& out, const Vector2& v)
	{
		out << "{ " << v.x << ", " << v.y << "}";

		return out;
	}
	bool isZero() const
	{
		// s-비교법을 사용한다. 
		// 0.00001 범위를 검사해 두 조건이 참일 때에만 return. 
		return (std::abs(x) < static_cast<float>(1e-5) && std::abs(y) < static_cast<float>(1e-5));

	}

	float sqrtMagnitude() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	void Normalize()
	{
		if (!isZero())
		{
			float magn = this->Magnitude();
			if (magn > 0)
			{
				x /= magn; 
				y /= magn; 
			}
		}
	}

	float Magnitude() const
	{
		return (x * x) + (y * y);
	}
	void Normalized() 
	{
		if (!isZero())
		{
			*this / this->sqrtMagnitude();
		}
		else
			Vector2(0.0f, 0.0f);
	}

	float Distance(const Vector2& from, const Vector2& to) const
	{
		Vector2 distance = to - from;
		return distance.sqrtMagnitude();
	}

	void Direction(const Vector2& other) const
	{

	}

	Vector2* operator->() {
		return this;
	}
	const Vector2* operator->() const {
		return this;
	}

	Vector2 Zero()
	{
		return Vector2(0, 0);
	}
	Vector2 One()
	{
		return Vector2(1, 1);
	}
private:
	float x;
	float y;
};

