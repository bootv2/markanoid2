#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFGUI\SFGUI.hpp>

#include <iostream>

#include "Engine.cpp"



int main(int argc, char* argv[])
{

	Engine game(true);

	try
	{
		return game.run();
	}
	catch (int& e)
	{
		switch (e)
		{
		case 1:
			std::cerr << "error loading game textures.(errno " << e << ")\n";
			return e;
			break;
		default:
			std::cerr << "Unknown fatal exception occured, the game will now exit\n";
			return e;
			break;
		}
	}
}