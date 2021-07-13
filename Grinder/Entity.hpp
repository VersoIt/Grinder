#pragma once
#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "SpriteManager.hpp"
#include "Manager.hpp"
#include "Vector.hpp"
#include "TextManager.hpp"
#include "SpriteManager.hpp"

namespace EngineComponents
{
	class Entity : public Manager, public TextManager, public SpriteManager
	{
	public:
		Entity(const std::string& path, int health = 10, float acceleration = 0.1f, const std::string& name = "")
			: SpriteManager(path), m_health{ health }, m_acceleration{ acceleration }, TextManager{ name }
		{
		}

		virtual void setPosition(const sf::Vector2f& pos) override { getSprite().setPosition(pos); };
		virtual void setRotation(float degrees) override { getSprite().setRotation(degrees); };

		virtual void move(sf::Vector2f offset) override { getSprite().move(offset); }
		virtual void rotate(float degrees) override { getSprite().rotate(degrees); };

		virtual void update(float time) = 0; // basic

		EngineUtility::Vector& getVector() { return m_vector; }
		const EngineUtility::Vector& getVector() const { return m_vector; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(getSprite(), states);
			if (getText().getString() != "")
				target.draw(getText(), states);
		}

	private:
		EngineUtility::Vector m_vector;
		std::string m_name;

		int m_health;
		float m_acceleration;

	};

}
#endif // _ENTITY_HPP_