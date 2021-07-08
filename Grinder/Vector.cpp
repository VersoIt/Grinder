#include "Vector.hpp"

namespace EngineUtility
{

	Vector& Vector::operator += (const Vector& other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

	Vector& Vector::operator -= (const Vector& other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}

	void Vector::reset() noexcept
	{
		m_x = 0.f;
		m_y = 0.f;
	}

	void Vector::normalize()
	{
		m_x /= m_length;
		m_y /= m_length;
	}

	std::ostream& operator << (std::ostream& os, const Vector vec)
	{
		os << "(" << vec.getX() << ", " << vec.getY() << ")" << std::endl;
		return os;
	}
}