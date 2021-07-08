#pragma once
#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

namespace EngineComponents
{
	class Manager
	{
	public:
		virtual void setSize(const sf::Vector2f& targetSize) = 0;
		virtual void setScale(const sf::Vector2f factors) = 0;

		virtual void setPosition(sf::Vector2f pos) = 0;
		virtual void setRotation(float degrees) = 0;

		virtual void move(sf::Vector2f offset) = 0;
		virtual void rotate(float degrees) = 0;

	};
}

#endif // _MANAGER_HPP_