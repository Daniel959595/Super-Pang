#pragma once

#include "SFML/Graphics.hpp"
#include "Utilities.h"

class Button
{
public:
	Button(const sf::Vector2f& pos, std::string& str, ButtonType type);
	void draw(sf::RenderWindow& window);
	bool handleClick(const sf::Vector2f& ClickPos) const;

private:
	void setRect(const sf::Vector2f& pos);
	void setFontAndText(const std::string& str);

public:
	const ButtonType m_type;

private:
	sf::RectangleShape m_rect;
	sf::Font m_font;
	sf::Text m_text;
};