#include "Button.hpp"
#include <iostream>

namespace EngineComponents
{
	Button::Button(const std::string& imagePath, const std::string& hoverPath, sf::Vector2f pos, std::function<void(void)> action, const std::string& text)
		: RenderObject(imagePath, text), m_action{ action }, m_hover{ hoverPath }, m_currentSprite{ imagePath }, m_isClicked{ false }
	{
		getSprite().setPosition(pos);
		m_hover.getSprite().setPosition(pos);
		getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
		m_hover.getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
		m_currentSprite.getSprite() = getSprite();
		m_currentSprite.getTexture() = getTexture();
		m_currentSprite.getTextureFilePath() = getTextureFilePath();

		getText().setCharacterSize(getTexture().getSize().y / 2.3f);
		getText().setLetterSpacing(1.3f);
		setFont("Fonts/Archive.ttf");
		getText().setPosition(getSprite().getPosition().x, getSprite().getPosition().y - getText().getLocalBounds().height / 2);

	}

	Button::Button(sf::Vector2f increase, const std::string& imagePath, const std::string& hoverPath, sf::Vector2f pos, std::function<void(void)> action, const std::string& text)
		: Button(imagePath, hoverPath, pos, action, text)
	{
		setScale(increase);

		getText().setOrigin(getText().getLocalBounds().width / 2, getText().getLocalBounds().height / 2);
		getText().setPosition(getSprite().getPosition().x, getSprite().getPosition().y - getText().getLocalBounds().height / 3);
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{ 
		SpriteManager::draw(target, states);
		target.draw(m_currentSprite.getSprite(), states);
		TextManager::draw(target, states);
	}

	void Button::setScale(const sf::Vector2f factors) 
	{ 
		RenderObject::setScale(factors);
		m_currentSprite.getSprite().setScale(factors);
		getHover().getSprite().setScale(factors);
	}

	void Button::setSize(const sf::Vector2f& targetSize)
	{
		RenderObject::setSize(targetSize);
		m_currentSprite.getSprite().setScale({ targetSize.x / getSprite().getLocalBounds().width, targetSize.y / getSprite().getLocalBounds().height });
		getHover().getSprite().setScale({ targetSize.x / getSprite().getLocalBounds().width, targetSize.y / getSprite().getLocalBounds().height });
	}

	void Button::setPosition(sf::Vector2f pos)
	{
		RenderObject::setPosition(pos);
		m_currentSprite.getSprite().setPosition(pos.x, pos.y);
		getHover().getSprite().setPosition(pos.x, pos.y);
	}

	void Button::setRotation(float degrees)
	{
		RenderObject::setRotation(degrees);
		getHover().getSprite().setRotation(degrees);
	}

	void Button::move(sf::Vector2f offset)
	{
		RenderObject::move(offset);
		getSprite().move(offset);
		getHover().getSprite().move(offset);
	}

	void Button::rotate(float degrees)
	{
		RenderObject::rotate(degrees);
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