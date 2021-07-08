#include "Button.hpp"
#include <iostream>

namespace EngineComponents
{
	Button::Button(const std::string& imagePath, const std::string& hoverPath, sf::Vector2f pos, std::function<void(void)> action, const std::string& name, const std::string& text)
		: GUIObject(imagePath, name), m_action{ action }, m_hover{ hoverPath }, m_currentSprite{ imagePath }, TextManager{ text }, m_isClicked{ false }
	{
		getSprite().setPosition(pos);
		m_hover.getSprite().setPosition(pos);
		getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
		m_hover.getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
		m_currentSprite.getSprite() = getSprite();
		m_currentSprite.getTexture() = getTexture();
		m_currentSprite.getTextureFilePath() = getTextureFilePath();
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{ 
		SpriteManager::draw(target, states);
		TextManager::draw(target, states);
		target.draw(m_currentSprite.getSprite(), states);
	}

	void Button::setScale(const sf::Vector2f factors) 
	{ 
		getSprite().setScale(factors); 
		getHover().getSprite().setScale(factors);
	}

	void Button::setSize(const sf::Vector2f& targetSize)
	{
		getSprite().setScale({ targetSize.x / getSprite().getLocalBounds().width, targetSize.y / getSprite().getLocalBounds().height });
		getHover().getSprite().setScale({ targetSize.x / getSprite().getLocalBounds().width, targetSize.y / getSprite().getLocalBounds().height });
	}

	void Button::setPosition(sf::Vector2f pos)
	{
		getSprite().setPosition(pos.x, pos.y);
		getHover().getSprite().setPosition(pos.x, pos.y);
	}

	void Button::setRotation(float degrees)
	{
		getSprite().setRotation(degrees);
		getHover().getSprite().setRotation(degrees);
	}

	void Button::move(sf::Vector2f offset)
	{
		getSprite().move(offset);
		getHover().getSprite().move(offset);
	}

	void Button::rotate(float degrees)
	{
		getSprite().rotate(degrees);
		getHover().getSprite().rotate(degrees);
	}

	void Button::catchMouseEvent(const sf::Event& event,const sf::Vector2i& mousePos)
	{
		if (getSprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			m_currentSprite = m_hover;
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_isClicked = true;
					m_currentSprite.getSprite() = getSprite();
					m_currentSprite.getTexture() = getTexture();
				}
			}
		}
		else
		{
			m_currentSprite.getSprite() = getSprite();
			m_currentSprite.getTexture() = getTexture();
		}

		if (m_isClicked)
		{
			m_currentSprite.getSprite() = getSprite();
			m_currentSprite.getTexture() = getTexture();
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (m_isClicked && getSprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
			{
				m_action();
				m_currentSprite = m_hover;
			}
			m_isClicked = false;
		}
	}
}