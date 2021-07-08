#include "ScrollField.hpp"
#include <iostream>

namespace EngineComponents
{
	ScrollField::ScrollField(sf::Window& window, Button* button, Button* minButton, Button* maxButton, std::string imagePath, std::string hoverPath, sf::Vector2f pos)
		: m_window{ window }, Button(imagePath, hoverPath, pos, [this]() {if (!m_button->getSprite().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)))m_button->setPosition({ static_cast<float>(sf::Mouse::getPosition(m_window).x),getSprite().getPosition().y }); }), m_button{ button }, m_minButton{ minButton }, m_maxButton{ maxButton }, m_isMove{ false }, m_dX{ 0 }, m_currentButton{ button }
	{
		if (m_button->getSprite().getPosition().x < getSprite().getPosition().x - getTexture().getSize().x / 2 || m_button->getSprite().getPosition().x > getSprite().getPosition().x + getTexture().getSize().x)
			m_button->getSprite().setPosition(static_cast<float>(getSprite().getPosition().x), m_button->getSprite().getPosition().y);
		m_maxButton->setPosition({ getSprite().getPosition().x + getTexture().getSize().x / 2 - m_maxButton->getTexture().getSize().x / 2, getSprite().getPosition().y });
		m_minButton->setPosition({ getSprite().getPosition().x - getTexture().getSize().x / 2 + m_maxButton->getTexture().getSize().x / 2, getSprite().getPosition().y });
		
		setFont("Fonts/Archive.ttf");
		getText().setCharacterSize(56);
		getText().setString(std::to_string(static_cast<int>(round(((m_currentButton->getSprite().getPosition().x - (getSprite().getPosition().x - getTexture().getSize().x / 2) - m_currentButton->getTexture().getSize().x / 2) * 100) / (getTexture().getSize().x - m_currentButton->getTexture().getSize().x)))) + '%');
		getText().setPosition(getSprite().getPosition().x + getTexture().getSize().x / 2 + m_currentButton->getTexture().getSize().x / 10, m_currentButton->getSprite().getPosition().y - getText().getGlobalBounds().height);
		
		m_shadowText = getText();
		m_shadowText.move(2.f, 2.f);
		m_shadowText.setFillColor(sf::Color(230, 132, 5));
	}

	void ScrollField::draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		Button::draw(target, state);
		target.draw(m_shadowText, state);
		target.draw((getText()), state);
		target.draw(*m_currentButton);
	}

	void ScrollField::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{

		Button::catchMouseEvent(event, mousePos);

		if (m_button->getSprite().getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				m_dX = mousePos.x - (m_button->getSprite().getPosition().x);
				m_isMove = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			m_isMove = false;
		}

		if (m_isMove)
		{
			m_button->setPosition({ static_cast<float>(mousePos.x) - m_dX, m_button->getSprite().getPosition().y });
			m_currentButton = m_button;
		}

		if (m_button->getSprite().getPosition().x >= getSprite().getPosition().x + getTexture().getSize().x / 2 - m_button->getTexture().getSize().x / 2)
		{
			m_button->setPosition({ getSprite().getPosition().x + getTexture().getSize().x / 2 - m_button->getTexture().getSize().x / 2, m_button->getSprite().getPosition().y });
			m_currentButton = m_maxButton;
		}

		if (m_button->getSprite().getPosition().x <= getSprite().getPosition().x - getTexture().getSize().x / 2 + m_button->getTexture().getSize().x / 2)
		{
			m_button->setPosition({ getSprite().getPosition().x - getTexture().getSize().x / 2 + m_button->getTexture().getSize().x / 2, m_button->getSprite().getPosition().y });
			m_currentButton = m_minButton;
		}

		getText().setString(std::to_string(static_cast<int>(ceil(((m_currentButton->getSprite().getPosition().x - (getSprite().getPosition().x - getTexture().getSize().x / 2) - m_currentButton->getTexture().getSize().x / 2) * 100) / (getTexture().getSize().x - m_currentButton->getTexture().getSize().x)))) + '%');
		m_shadowText.setString(std::to_string(static_cast<int>(ceil(((m_currentButton->getSprite().getPosition().x - (getSprite().getPosition().x - getTexture().getSize().x / 2) - m_currentButton->getTexture().getSize().x / 2) * 100) / (getTexture().getSize().x - m_currentButton->getTexture().getSize().x)))) + '%');
		m_currentButton->catchMouseEvent(event, mousePos);
	}


	ScrollField::~ScrollField() { delete m_button; delete m_minButton; delete m_maxButton; }
}