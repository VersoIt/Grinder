#include "Button.hpp"
#include <iostream>

namespace EngineComponents
{
	Button::Button(const std::string& imagePath, const std::string& hoverPath, std::function<void(void)> action, const sf::Vector2f& pos, const std::string& str)
		: RenderObject(imagePath, str, pos), m_action{ action }, m_hover{ hoverPath, pos }, m_isClicked{ false }
	{
		m_currentSprite.sprite = sprite;
		m_currentSprite.texture = texture;
		m_currentSprite.getTextureFilePath() = getTextureFilePath();

		text.setCharacterSize(static_cast<unsigned int>(texture.getSize().y / 2.3f));
		text.setLetterSpacing(1.3f);
		setFont("Fonts/Archive.ttf");
		text.setPosition(sprite.getPosition().x, sprite.getPosition().y - text.getLocalBounds().height / 2);
	}

	Button::Button(sf::Vector2f increase, const std::string& imagePath, const std::string& hoverPath, std::function<void(void)> action, const sf::Vector2f& pos, const std::string& str)
		: Button(imagePath, hoverPath, action, pos, str)
	{
		setScale(increase);

		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(sprite.getPosition().x, sprite.getPosition().y - text.getLocalBounds().height / 3);
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{ 
		SpriteManager::draw(target, states);
		target.draw(m_currentSprite.sprite, states);
		TextManager::draw(target, states);
	}

	void Button::setScale(const sf::Vector2f factors) 
	{ 
		RenderObject::setScale(factors);
		m_currentSprite.sprite.setScale(factors);
		getHover().sprite.setScale(factors);
	}

	void Button::setSize(const sf::Vector2f& targetSize)
	{
		RenderObject::setSize(targetSize);
		m_currentSprite.sprite.setScale({ targetSize.x / sprite.getLocalBounds().width, targetSize.y / sprite.getLocalBounds().height });
		getHover().sprite.setScale({ targetSize.x / sprite.getLocalBounds().width, targetSize.y / sprite.getLocalBounds().height });
	}

	void Button::setPosition(const sf::Vector2f& pos)
	{
		RenderObject::setPosition(pos);
		m_currentSprite.sprite.setPosition(pos.x, pos.y);
		getHover().sprite.setPosition(pos.x, pos.y);
	}

	void Button::setRotation(float degrees)
	{
		RenderObject::setRotation(degrees);
		getHover().sprite.setRotation(degrees);
	}

	void Button::move(sf::Vector2f offset)
	{
		RenderObject::move(offset);
		getHover().sprite.move(offset);
		m_currentSprite.sprite.move(offset);
	}

	void Button::rotate(float degrees)
	{
		RenderObject::rotate(degrees);
		getHover().sprite.rotate(degrees);
	}

	void Button::catchMouseEvent(const sf::Event& event,const sf::Vector2i& mousePos)
	{
		if (sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			m_currentSprite = m_hover;
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_isClicked = true;
					m_currentSprite.sprite = sprite;
					m_currentSprite.texture = texture;
				}
			}
		}
		else
		{
			m_currentSprite.sprite = sprite;
			m_currentSprite.texture = texture;
		}

		if (m_isClicked)
		{
			m_currentSprite.sprite = sprite;
			m_currentSprite.texture = texture;
		}


		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (m_isClicked && sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
			{
				m_currentSprite = m_hover;
				m_action();
			}
			m_isClicked = false;
		}
	}
}