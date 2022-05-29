#include "BaseButton.h"

BaseButton::BaseButton(sf::Vector2f pos, std::string str)
{
	setRect(pos);
	setFontAndText(str);
}

void BaseButton::draw(sf::RenderWindow& window)
{
	window.draw(m_rect);
	window.draw(m_text);
}

bool BaseButton::handleClick(const sf::Vector2f& ClickPos) const
{
	return (m_rect.getGlobalBounds().contains(ClickPos) ? true : false);
}

void BaseButton::setRect(sf::Vector2f pos)
{
	m_rect.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_rect.setPosition(pos);
	m_rect.setFillColor(sf::Color::Transparent);
}

void BaseButton::setFontAndText(std::string str)
{
	m_font.loadFromFile("Retro.ttf");
	m_text.setFont(m_font);
	m_text.setString(str);
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::Red);

	float x = m_rect.getGlobalBounds().left + ((BUTTON_WIDTH - m_text.getGlobalBounds().width) / 2);
	float y = m_rect.getGlobalBounds().top + ((BUTTON_HEIGHT - m_text.getGlobalBounds().height) / 2);
	m_text.setPosition(sf::Vector2f(x, y));
}
