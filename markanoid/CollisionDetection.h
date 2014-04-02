#pragma once
#include <SFML/Graphics.hpp>
template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
};

/*template<class T1, const class T2> bool isIntersecting(T1& mA, const T2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() && mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
};*/

template<class T2> bool isIntersecting(sf::RectangleShape _shape, T2& mB)
{
	return _shape.getPosition().x + _shape.getSize().x >= mB.left() && _shape.getPosition().x <= mB.right() &&
		_shape.getPosition().y >= mB.top() && _shape.getPosition().y + _shape.getSize().y <= mB.bottom();
};