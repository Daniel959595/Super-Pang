#pragma once

#include "SFML/Graphics.hpp"
#include "Utilities.h"
#include "BaseButton.h"
#include <functional>

template <typename FN>
class Button : public BaseButton
{
public:
	//using BaseButton::BaseButton();

	//Button(const sf::Vector2f& pos, std::string& str, FN func);
	Button(sf::Vector2f pos, std::string str, FN f);
	virtual ~Button() = default;

	//virtual void runAction() override;
private:
	FN m_func;
	virtual void runAction() override;
};


//template<typename FN>
//Button<FN>::Button(const sf::Vector2f& pos, std::string& str, FN func) : BaseButton(pos, str), m_func(func)
//{
//
//}

template<typename FN>
Button<FN>::Button(sf::Vector2f pos, std::string str, FN f) : BaseButton(pos, str), m_func(f)
{

}

template<typename FN>
void Button<FN>::runAction()
{
	m_func();
}
