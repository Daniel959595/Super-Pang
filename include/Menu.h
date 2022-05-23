#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

#include "Button.h"

class Menu
{
public:
	Menu();

	void handleMenu(sf::RenderWindow& window, sf::View& view);

private:
	void setTextureAndSprite();
	void draw(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window, sf::View& view);
	void resizeView(sf::RenderWindow& window, sf::View& view, sf::Event& event);
	void handleClick(sf::Vector2f& clickLocation);
	void runAction(ButtonType type);

public:


private:
	sf::Texture m_texture;
	sf::Sprite m_backGround;
	std::vector<Button> m_buttons;
};