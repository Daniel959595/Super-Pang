#include "BaseButton.h"

BaseButton::BaseButton(sf::Vector2f pos, std::string str)
	: m_font(Resources::instance().getFont())
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
	m_text.setFont(m_font);
	m_text.setString(str);
	m_text.setCharacterSize(80);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineThickness(3);
	m_text.setOutlineColor(sf::Color{ 0,102,102 });

	float x = m_rect.getGlobalBounds().left + ((BUTTON_WIDTH - m_text.getGlobalBounds().width) / 2);
	float y = m_rect.getGlobalBounds().top + ((BUTTON_HEIGHT - m_text.getGlobalBounds().height) / 2);
	m_text.setPosition(sf::Vector2f(x, y));
}
