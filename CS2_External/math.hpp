#pragma once
#include <math.h>
#include "Cheats.h"
#include <vector>


class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(float x, float y)
	{
		this->x = x; this->y = y;
	}

	Vector2D(const Vector2D& vecBase)
	{
		this->x = vecBase.x; this->y = vecBase.y;
	}

	bool IsValid() const
	{
		return std::isfinite(this->x) && std::isfinite(this->y);
	}

	constexpr void Invalidate()
	{
		this->x = this->y = std::numeric_limits<float>::infinity();
	}

	constexpr float operator[](std::size_t nIndex) const
	{
		return ((float*)this)[nIndex];
	}

	constexpr float& operator[](std::size_t nIndex)
	{
		return ((float*)this)[nIndex];
	}

	bool operator==(const Vector2D& vecBase) const
	{
		return this->IsEqual(vecBase);
	}

	bool operator!=(const Vector2D& vecBase) const
	{
		return !this->IsEqual(vecBase);
	}

	constexpr Vector2D& operator=(const Vector2D& vecBase)
	{
		this->x = vecBase.x; this->y = vecBase.y;
		return *this;
	}

	constexpr Vector2D& operator+=(const Vector2D& vecBase)
	{
		this->x += vecBase.x; this->y += vecBase.y;
		return *this;
	}

	constexpr Vector2D& operator-=(const Vector2D& vecBase)
	{
		this->x -= vecBase.x; this->y -= vecBase.y;
		return *this;
	}

	constexpr Vector2D& operator*=(const Vector2D& vecBase)
	{
		this->x *= vecBase.x; this->y *= vecBase.y;
		return *this;
	}

	constexpr Vector2D& operator/=(const Vector2D& vecBase)
	{
		this->x /= vecBase.x; this->y /= vecBase.y;
		return *this;
	}

	constexpr Vector2D& operator+=(float flAdd)
	{
		this->x += flAdd; this->y += flAdd;
		return *this;
	}

	constexpr Vector2D& operator-=(float flSubtract)
	{
		this->x -= flSubtract; this->y -= flSubtract;
		return *this;
	}

	constexpr Vector2D& operator*=(float flMultiply)
	{
		this->x *= flMultiply; this->y *= flMultiply;
		return *this;
	}

	constexpr Vector2D& operator/=(float flDivide)
	{
		this->x /= flDivide; this->y /= flDivide;
		return *this;
	}

	constexpr bool operator<(const Vector2D& vecOther) const
	{
		return (x < vecOther.x && y < vecOther.y);
	}

	constexpr bool operator>(const Vector2D& vecOther) const
	{
		return (x > vecOther.x && y > vecOther.y);
	}

	Vector2D operator+(const Vector2D& vecAdd) const
	{
		return Vector2D(this->x + vecAdd.x, this->y + vecAdd.y);
	}

	Vector2D operator-(const Vector2D& vecSubtract) const
	{
		return Vector2D(this->x - vecSubtract.x, this->y - vecSubtract.y);
	}

	Vector2D operator*(const Vector2D& vecMultiply) const
	{
		return Vector2D(this->x * vecMultiply.x, this->y * vecMultiply.y);
	}

	Vector2D operator/(const Vector2D& vecDivide) const {
		return Vector2D(this->x / vecDivide.x, this->y / vecDivide.y);
	}

	Vector2D operator+(float flAdd) const
	{
		return Vector2D(this->x + flAdd, this->y + flAdd);
	}

	Vector2D operator-(float flSubtract) const
	{
		return Vector2D(this->x - flSubtract, this->y - flSubtract);
	}

	Vector2D operator*(float flMultiply) const
	{
		return Vector2D(this->x * flMultiply, this->y * flMultiply);
	}

	Vector2D operator/(float flDivide) const
	{
		return Vector2D(this->x / flDivide, this->y / flDivide);
	}

	bool IsEqual(const Vector2D& vecEqual) const
	{
		return (std::fabsf(this->x - vecEqual.x) < std::numeric_limits<float>::epsilon() &&
			std::fabsf(this->y - vecEqual.y) < std::numeric_limits<float>::epsilon());
	}

	bool IsZero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO);
	}

	Vector2D ToVector2D()
	{
		return Vector2D(this->x, this->y);
	}

	float Length() const
	{
		return std::sqrtf(this->x * this->x + this->y * this->y);
	}

	constexpr float LengthSqr() const
	{
		return (this->x * this->x + this->y * this->y);
	}

	float DistTo(const Vector2D& vecEnd) const
	{
		return (*this - vecEnd).Length();
	}

	float DistToSqr(const Vector2D& vecEnd) const
	{
		return (*this - vecEnd).LengthSqr();
	}

	void Normalize()
	{
		float flLength = this->Length();

		if (flLength != 0.0f)
			*this /= flLength;
		else
			this->x = this->y = 0.0f;
	}

public:
	float x, y;
};

namespace math {
	constexpr float pi = 3.1415926535897932384f; // pi
	constexpr float pi_2 = pi * 2.f;               // pi * 2
	constexpr float rad_pi{ 57.295779513082f };

	float degrees_to_radians(const float deg)
	{
		return deg * (pi / 180.f);
	}

	float radians_to_degrees(const float rad)
	{
		return rad * rad_pi;
	}

	void rotate_triangle(std::array<Vector2D, 3>& points, float rotation)
	{
		const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
		for (auto& point : points)
		{
			point -= points_center;

			const auto temp_x = point.x;
			const auto temp_y = point.y;

			const auto theta = degrees_to_radians(rotation);
			const auto c = cosf(theta);
			const auto s = sinf(theta);

			point.x = temp_x * c - temp_y * s;
			point.y = temp_x * s + temp_y * c;

			point += points_center;
		}
	}

	Vec3 calc_angle(const Vec3& a, const Vec3& b)
	{
		Vec3 angles;

		Vec3 delta = { a.x - b.x, a.y - b.y, a.z - b.z };
		float hyp = delta.Length(); 

		angles.y = std::atan2(delta.y, delta.x) * math::rad_pi;
		angles.x = std::atan2(-delta.z, hyp) * -math::rad_pi;
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		return angles;
	}

	float normalize_yaw(float yaw)
	{
		while (yaw < -180.f)
			yaw += 360.f;
		while (yaw > 180.f)
			yaw -= 360.f;

		return yaw;
	}


}
