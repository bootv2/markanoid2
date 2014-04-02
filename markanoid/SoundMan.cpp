#include <SFML\Audio.hpp>
#include <map>
#include <iostream>
#include <string>
#include <random>
#include <time.h>

#include "SoundMan.h"


SoundMan::SoundMan()
{
	sndMap["blockDestroyed0"].loadFromFile("res/snd/blockdestroyed.ogg");
	sndMap["blockDestroyed1"].loadFromFile("res/snd/blockdestroyed2.wav");
	sndMap["blockDestroyed2"].loadFromFile("res/snd/blockdestroyed3.wav");
	sndMap["blockDestroyed3"].loadFromFile("res/snd/blockdestroyed4.wav");

	sndMap["gameOver"].loadFromFile("res/snd/gameOver.wav");
	sndMap["startgame"].loadFromFile("res/snd/startGame.wav");

	sndMap["laser"].loadFromFile("res/snd/laser.wav");
	sndMap["slow"].loadFromFile("res/snd/slow.ogg");
	sndMap["widepaddle"].loadFromFile("res/snd/widepaddle.wav");
	sndMap["tripleball"].loadFromFile("res/snd/tripleball.wav");
	sndMap["undowidepaddle"].loadFromFile("res/snd/thinpaddle.wav");

	sndMap["lostlife"].loadFromFile("res/snd/lostlife.wav");

	sndMap["powpickup"].loadFromFile("res/snd/powpickup.wav");
	sndMap["powselect"].loadFromFile("res/snd/powselect.ogg");

}

void SoundMan::addSound(std::string name, std::string path)
{
	sndMap[name].loadFromFile(path);
}

void SoundMan::playPowSound(int id)
{
	int channelToUse = getFreeChannel();
	if (channelToUse == -1) return;
			playing[channelToUse] = true;
			switch (id)
			{
			case 0:
				playable[channelToUse].setBuffer(sndMap["laser"]);
				break;
			case 1:
				playable[channelToUse].setBuffer(sndMap["tripleball"]);
				break;
			case 2:
				playable[channelToUse].setBuffer(sndMap["widepaddle"]);
				break;
			case 3:
				//playable[channelToUse].setBuffer(sndMap[name]); GAIN LIFE
				break;
			case 4:
				playable[channelToUse].setBuffer(sndMap["slow"]);
				break;
			case 5:
				//playable[channelToUse].setBuffer(sndMap[name]); BIG BALL
				break;
			}
			playable[channelToUse].play();
			
}

void SoundMan::playBlockBreakSound()
{
	int channelToUse = getFreeChannel();
	if (channelToUse == -1) return;
	switch (rand() % 4)
	{
	case 0:
		playable[channelToUse].setBuffer(sndMap["blockDestroyed0"]);
		break;
	case 1:
		playable[channelToUse].setBuffer(sndMap["blockDestroyed1"]);
		break;
	case 2:
		playable[channelToUse].setBuffer(sndMap["blockDestroyed2"]);
		break;
	case 3:
		playable[channelToUse].setBuffer(sndMap["blockDestroyed3"]);
		break;
	}
	playing[channelToUse] = true;
	playable[channelToUse].play();
}

void SoundMan::checkPlaying()
{
	for (int i = 0; i < 32; i++)
	{
		if (playable[i].getStatus() == playable[i].Stopped)
		{
			playing[i] = false;
		}
			
	}
}

int SoundMan::getFreeChannel()
{
	checkPlaying();
	for (int i = 0; i < 32; i++)
	{
		if (!playing[i]) return i;
	}
	std::cout << "No free channels found!\n";
	return -1;
}

void SoundMan::playPowDeactivationSound(int id)
{

}

void SoundMan::playGameStartSound()
{

}

void SoundMan::playButtonSound()
{

}

void SoundMan::playLifeLostSound()
{

}

void SoundMan::playGameOverSound()
{

}

void SoundMan::playSoundFromName(std::string name)
{

}

SoundMan::~SoundMan()
{
}
