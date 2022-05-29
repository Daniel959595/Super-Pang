#include "Button.h"
//
////Button::Button(const sf::Vector2f& pos, std::string& str, ButtonType type)
////{
////	setRect(pos);
////	setFontAndText(str);
////}
//
//template<typename FN>
//Button<FN>::Button(const sf::Vector2f& pos, std::string& str, FN func) : m_func(func)
//{
//	setRect(pos);
//	setFontAndText(str);
//}
//
//template<typename FN>
//void Button<FN>::draw(sf::RenderWindow& window)
//{
//	window.draw(m_rect);
//	window.draw(m_text);
//}
//
//template<typename FN>
//bool Button<FN>::handleClick(const sf::Vector2f& ClickPos) const
//{
//	return false;
//}
//
//template<typename FN>
//void Button<FN>::setRect(const sf::Vector2f& pos)
//{
//	m_rect.setPosition(pos);
//	m_rect.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
//}
//
//template<typename FN>
//void Button<FN>::setFontAndText(const std::string& str)
//{
//	m_font.loadFromFile("c:/Windows/Fonts/arial.ttf");
//	m_text.setFont(m_font);
//	m_text.setString(str);
//	m_text.setCharacterSize(50);
//	m_text.setFillColor(sf::Color::Red);
//
//	float x = m_rect.getGlobalBounds().left + ((BUTTON_WIDTH - m_text.getGlobalBounds().width) / 2);
//	float y = m_rect.getGlobalBounds().top + ((BUTTON_HEIGHT - m_text.getGlobalBounds().height) / 2);
//	m_text.setPosition(sf::Vector2f(x, y));
//}
