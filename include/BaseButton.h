#pragma once

#include "SFML/Graphics.hpp"
#include "Utilities.h"

class BaseButton
{
public:
	BaseButton(sf::Vector2f pos, std::string str);
	virtual ~BaseButton() = default;

	void draw(sf::RenderWindow& window);
	bool handleClick(const sf::Vector2f& ClickPos) const;
	
	virtual void runAction() = 0 {};

private:
	void setRect(sf::Vector2f pos);
	void setFontAndText(std::string str);

public:

private:
	sf::RectangleShape m_rect;
	sf::Font m_font;
	sf::Text m_text;
};