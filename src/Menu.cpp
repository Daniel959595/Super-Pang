#include "Menu.h"



Menu::Menu()
{
    setTextureAndSprite();
}

void Menu::handleMenu(sf::RenderWindow& window, sf::View& view)
{
	while (window.isOpen() && ! m_exit) {
		draw(window);
		handleEvents(window, view);
	}
}

void Menu::addButton(std::unique_ptr<BaseButton> button)
{
    m_buttons.push_back(std::move(button));
}


void Menu::setTextureAndSprite()
{
    m_texture.loadFromFile("menuBackGround.jpg");
    m_backGround.setTexture(m_texture);

    float factorX = WINDOW_WIDTH  / m_backGround.getGlobalBounds().width;
    float factorY = WINDOW_HEIGHT / m_backGround.getGlobalBounds().height;
    m_backGround.scale(sf::Vector2f(factorX, factorY));
}

void Menu::draw(sf::RenderWindow& window)
{
	window.clear();
    window.draw(m_backGround);
	for (auto& b : m_buttons) {
		(b)->draw(window);
	}
	window.display();
}

void Menu::handleEvents(sf::RenderWindow& window, sf::View& view)
{
    sf::Vector2f location;
    if (auto event = sf::Event{}; window.waitEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close(); break;
        case sf::Event::Resized:
            resizeView(window, view, event); break;
        case sf::Event::MouseButtonReleased:
            location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
            handleClick(location); break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                m_exit = true; break;
            }
        }
    }
}

void Menu::resizeView(sf::RenderWindow& window, sf::View& view, sf::Event& event)
{
    view.setSize(float(event.size.width), float(event.size.height));
    window.setView(view);
}

void Menu::handleClick(sf::Vector2f& clickLocation)
{
    for (auto& b : m_buttons) {
        if ((b)->handleClick(clickLocation))
            (b)->runAction();
    }
}

void Menu::runAction(ButtonType type)
{
    switch (type)
    {
    case ButtonType::START:
    default:
        break;
    }
}

