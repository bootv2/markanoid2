#pragma once
class CollidableRect
{
public:
	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float left()	{ return x() - shape.getSize().x / 2; }
	float right()	{ return x() + shape.getSize().x / 2; }
	float top()		{ return y() - shape.getSize().y / 2; }
	float bottom()	{ return y() + shape.getSize().y / 2; }
	CollidableRect()
	{

	}
	~CollidableRect()
	{

	}
	sf::RectangleShape shape;
};


class CollidableCircle
{
public:
	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float left()	{ return x() - shape.getRadius(); }
	float right()	{ return x() + shape.getRadius(); }
	float top()		{ return y() - shape.getRadius(); }
	float bottom()	{ return y() + shape.getRadius(); }
	CollidableCircle()
	{

	}
	~CollidableCircle()
	{

	}
	sf::CircleShape shape;
};
