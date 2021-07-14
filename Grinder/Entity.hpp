#pragma once
#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "EventObject.hpp"
#include "Vector.hpp"

namespace EngineComponents
{
	class Entity : public EventObject
	{
	public:
		Entity(const std::string& backgroundPath, int health = 10, float acceleration = 0.1f, const std::string& name = "")
			: EventObject(backgroundPath, name), m_health{ health }, m_acceleration{ acceleration }
		{
		}

		virtual void setPosition(const sf::Vector2f& pos) override { sprite.setPosition(pos); };
		virtual void setRotation(float degrees) override { sprite.setRotation(degrees); };

		virtual void move(sf::Vector2f offset) override { sprite.move(offset); }
		virtual void rotate(float degrees) override { sprite.rotate(degrees); };

		virtual void update(float time) = 0; // basic

		EngineUtility::Vector& getVector() { return m_vector; }
		const EngineUtility::Vector& getVector() const { return m_vector; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		EngineUtility::Vector m_vector;
		std::string m_name;

		int m_health;
		float m_acceleration;

	};

}
#endif // _ENTITY_HPP_