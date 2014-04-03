#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <string>
#include <iostream>

#include "collisiondetection.h" 

#include "soundman.h"
#include "keyBinds.h"
#include "ResMan.cpp"
#include "Settings.cpp"
#include "FileIO.cpp"
#include "timer.cpp"
#include "Score.h"
#include "collidableobject.h"
#include "lastframecollisions.h"
#include "score.h"
#include "Ball.h"
#include "block.h"


#include "Laser.h"


Laser::Laser(std::vector<Block>* _pBlockStorage, Score* _score)
{
	pScore = _score;
	pBlockStorage = _pBlockStorage;
}

void Laser::prepCollision(sf::Vector2f coordinates, float paddlesize, int windowHeight)
{
	shape.setSize(sf::Vector2f(paddlesize, windowHeight));
	shape.setPosition(coordinates.x, 0);
	windowheight = windowHeight;
}

Laser::~Laser()
{
}
