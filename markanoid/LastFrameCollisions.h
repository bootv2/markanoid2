#pragma once
struct LastFrameCollisions
{
public:
	std::map<int, bool> blockColls;
	bool leftBorder, rightBorder, topBorder;
};

