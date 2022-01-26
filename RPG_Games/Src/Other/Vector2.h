#pragma once
#include <cmath>

class Vector2
{
public:
	int x, y;
	
	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Vector2(int value[2])
	{
		x = value[0];
		y = value[1];
	}

	Vector2(Vector2& copy)
	{
		x = copy.x;
		y = copy.y;
	}

	~Vector2() = default;

	// ���g�Ƒ��x�N�^�[�Ƃ̋���.
	int Distance(Vector2 vec) 
	{
		int disX, disY;
		disX = vec.x - x;
		disY = vec.y - y;

		return sqrtf(disX * disX + disY * disY);
	}

	/*�@�l�����Z�@*/
	Vector2 operator +(Vector2 vec) { return Vector2(x + vec.x, y + vec.y); }
	Vector2 operator -(Vector2 vec) { return Vector2(x - vec.x, y - vec.y); }
	Vector2 operator *(Vector2 vec) { return Vector2(x * vec.x, y * vec.y); }
	Vector2 operator /(Vector2 vec) { return Vector2(x / vec.x, y / vec.y); }
	Vector2 operator %(Vector2 vec) { return Vector2(x % vec.x, y % vec.y); }

	/* ����E������Z */
	void operator =(Vector2 vec)  { x = vec.x;  y = vec.y; }
	void operator +=(Vector2 vec) { x += vec.x; y += vec.y; }
	void operator -=(Vector2 vec) { x -= vec.x; y -= vec.y; }
	void operator *=(Vector2 vec) { x *= vec.x; y *= vec.y; }
	void operator /=(Vector2 vec) { x /= vec.x; y /= vec.y; }

	/* �������Z */
	bool operator ==(Vector2 vec) { return x == vec.x && y == vec.y; }
	bool operator !=(Vector2 vec) { return x != vec.x || y != vec.y; }
};

class Vector2D
{
public:
	double x, y;

	Vector2D(double _x, double _y)
	{
		x = _x;
		y = _y;
	}

	Vector2D(double value[2])
	{
		x = value[0];
		y = value[1];
	}

	Vector2D(Vector2D& copy)
	{
		x = copy.x;
		y = copy.y;
	}

	~Vector2D() = default;

	// ���g�Ƒ��x�N�^�[�Ƃ̋���.
	double Distance(Vector2D vec)
	{
		double disX, disY;
		disX = vec.x - x;
		disY = vec.y - y;

		return sqrtf(disX * disX + disY * disY);
	}

	/*�@�l�����Z�@*/
	Vector2D operator +(Vector2D vec) { return Vector2D(x + vec.x, y + vec.y); }
	Vector2D operator -(Vector2D vec) { return Vector2D(x - vec.x, y - vec.y); }
	Vector2D operator *(Vector2D vec) { return Vector2D(x * vec.x, y * vec.y); }
	Vector2D operator /(Vector2D vec) { return Vector2D(x / vec.x, y / vec.y); }

	/* ������Z */
	void operator =(Vector2D vec)  { x = vec.x;  y = vec.y; }
	void operator +=(Vector2D vec) { x += vec.x; y += vec.y; }
	void operator -=(Vector2D vec) { x -= vec.x; y -= vec.y; }
	void operator *=(Vector2D vec) { x *= vec.x; y *= vec.y; }
	void operator /=(Vector2D vec) { x /= vec.x; y /= vec.y; }

	/* �������Z */
	bool operator ==(Vector2D vec) { return x == vec.x && y == vec.y; }
	bool operator !=(Vector2D vec) { return x != vec.x || y != vec.y; }

	/* �ϊ��֌W */
	operator Vector2() { return Vector2(x, y); }
};