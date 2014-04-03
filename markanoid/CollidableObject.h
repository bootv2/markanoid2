#pragma once
class CollidableRect
{
public:
	float x()		{ return shape.getPosition().x; }
	float y()		{ return shape.getPosition().y; }
	float left()	{ return x(); }
	float right()	{ return x() + shape.getSize().x; }
	float top()		{ return 0; }
	float bottom()	{ return windowheight; }
	CollidableRect()
	{

	}
	~CollidableRect()
	{

	}
	sf::RectangleShape shape;
	int windowheight = 0;
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
