#pragma once

struct Vector3
{
	Vector3()
	{
		this->Set(0.0f, 0.0f, 0.0f);
	}

	Vector3(float x, float y, float z)
	{
		this->Set(x, y, z);
	}

	void Set(float newX, float newY, float newZ)
	{
		this->x = newX;
		this->y = newY;
		this->z = newZ;
	}

	float x, y, z;
};

struct Vector2
{
	Vector2()
	{
		this->Set(0.0f, 0.0f);
	}

	Vector2(float x, float y)
	{
		this->Set(x, y);
	}

	void Set(float newX, float newY)
	{
		this->x = newX;
		this->y = newY;
	}

	float x, y;
};

struct QAngle
{
	QAngle()
	{
		this->Set(0.0f, 0.0f, 0.0f);
	}

	QAngle(float x, float y, float z)
	{
		this->Set(x, y, z);
	}

	void Set(float newX, float newY, float newZ)
	{
		this->x = newX;
		this->y = newY;
		this->z = newZ;
	}

	float x, y, z;
};
