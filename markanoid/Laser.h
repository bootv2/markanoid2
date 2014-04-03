#pragma once
#include "CollidableObject.h"
class Laser : public CollidableRect
{
	Score* pScore;
	std::vector<Block>* pBlockStorage;
public:
	Laser(std::vector<Block>* _pBlockStorage, Score* _score);
	void prepCollision(sf::Vector2f coordinates, float paddlesize, int windowHeight);
	~Laser();
};

