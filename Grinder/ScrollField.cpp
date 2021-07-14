#include "ScrollField.hpp"
#include <iostream>

namespace EngineComponents
{
	ScrollField::ScrollField(sf::Window& window, Button* button, Button* minButton, Button* maxButton, std::string imagePath, std::string hoverPath, const sf::Vector2f& pos, int share)
		: m_window{ window }, Button(imagePath, hoverPath, [this]() {if (!m_button->sprite.getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))m_button->setPosition({ static_cast<float>(sf::Mouse::getPosition(m_window).x),sprite.getPosition().y }); }, pos), m_button{ button }, m_minButton{ minButton }, m_maxButton{ maxButton }, m_isMove{ false }, m_dX{ 0 }, m_currentButton{ button }, m_share{ share }
	{

		m_share < 100 ? m_share < 0 ? m_share = 0 : m_share : m_share = 100;

		m_currentButton->setPosition({ static_cast<float>(round(((texture.getSize().x - m_currentButton->texture.getSize().x) * m_share) / 100 + sprite.getPosition().x - texture.getSize().x / 2 + m_currentButton->texture.getSize().x / 2)), sprite.getPosition().y });
		m_maxButton->setPosition({ sprite.getPosition().x + texture.getSize().x / 2 - m_maxButton->texture.getSize().x / 2, sprite.getPosition().y });
		m_minButton->setPosition({ sprite.getPosition().x - texture.getSize().x / 2 + m_maxButton->texture.getSize().x / 2, sprite.getPosition().y });
		
		setFont("Fonts/Archive.ttf");
		text.setCharacterSize(56);
		text.setString(std::to_string(m_share) + '%');
		text.setPosition(sprite.getPosition().x + texture.getSize().x / 2 + m_currentButton->texture.getSize().x / 10, m_currentButton->sprite.getPosition().y - text.getGlobalBounds().height);
		
		m_shadowText = text;
		m_shadowText.move(2.f, 2.f);
		m_shadowText.setFillColor(sf::Color(230, 132, 5));
	}

	void ScrollField::draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		Button::draw(target, state);
		target.draw(m_shadowText, state);
		target.draw((text), state);
		target.draw(*m_currentButton);
	}

	void ScrollField::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{

		if (sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			getCurrentSprite() = getHover();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					getAction()();
					getCurrentSprite().sprite = sprite;
					getCurrentSprite().texture = texture;
				}
			}
		}
		else
		{
			getCurrentSprite().sprite = sprite;
			getCurrentSprite().texture = texture;
		}

		if (m_button->sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_dX = mousePos.x - (m_button->sprite.getPosition().x);
					m_isMove = true;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && m_isMove)
		{
			m_isMove = false;
		}

		if (m_isMove)
		{
			m_button->setPosition({ static_cast<float>(mousePos.x) - m_dX, m_button->sprite.getPosition().y });
			m_currentButton = m_button;
		}

		if (m_button->sprite.getPosition().x >= sprite.getPosition().x + texture.getSize().x / 2 - m_button->texture.getSize().x / 2)
		{
			m_button->setPosition({ sprite.getPosition().x + texture.getSize().x / 2 - m_button->texture.getSize().x / 2, m_button->sprite.getPosition().y });
			m_currentButton = m_maxButton;
		}

		if (m_button->sprite.getPosition().x <= sprite.getPosition().x - texture.getSize().x / 2 + m_button->texture.getSize().x / 2)
		{
			m_button->setPosition({ sprite.getPosition().x - texture.getSize().x / 2 + m_button->texture.getSize().x / 2, m_button->sprite.getPosition().y });
			m_currentButton = m_minButton;
		}

		m_share = static_cast<int>(round((((m_currentButton->sprite.getPosition().x - (sprite.getPosition().x - texture.getSize().x / 2) - m_currentButton->texture.getSize().x / 2) * 100) / (texture.getSize().x - m_currentButton->texture.getSize().x))));
		text.setString(std::to_string(m_share) + '%');
		m_shadowText.setString(std::to_string(m_share) + '%');
		m_currentButton->catchMouseEvent(event, mousePos);
	}

	ScrollField::~ScrollField() { delete m_button; delete m_minButton; delete m_maxButton; }
}