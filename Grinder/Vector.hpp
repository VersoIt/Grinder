#pragma once
#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

namespace EngineUtility
{
	class Vector
	{
		float m_x;
		float m_y;

		float m_length;

	public:
		Vector(float x = 0.f , float y = 0.f)
			: m_x{ x }, m_y{ y }, m_length{ static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2))) }
		{
		}

		static float convertToDegrees(float radians) { return static_cast<float>(radians * 180 / M_PI); }

		void normalize();

		float getX() const noexcept { return m_x; }
		float getY() const noexcept { return m_y; }

		float getLength() const noexcept { return m_length; }

		void setX(float x) noexcept { m_x = x; }
		void setY(float y) noexcept { m_y = y; }

		std::pair<Vector, Vector> crossVectors() { return std::pair<Vector, Vector>(Vector(-m_y, m_x), Vector(m_y, -m_x)); }

		float getRadiansBetween(const Vector& vec) const noexcept { return acos(vec.operator*(*this) / (this->m_length * vec.m_length)); }

		Vector operator + (const Vector& other) const { return Vector(m_x + other.m_x, m_y + other.m_y); }
		Vector& operator += (const Vector& other);

		Vector operator - (const Vector& other) const { return Vector(m_x - other.m_x, m_y - other.m_y); }
		Vector& operator -= (const Vector& other);

		float operator* (const Vector& other) const { return m_x * other.m_x + m_y * other.m_y; }

		void reset() noexcept;

		bool operator == (const Vector& other) const { return m_x == other.m_x && m_y == other.m_y; }
		Vector operator - () noexcept { return Vector(-m_x, -m_y); }

		friend std::ostream& operator << (std::ostream& os, const Vector vec);
	};
}

#endif // _VECTOR_HPP_