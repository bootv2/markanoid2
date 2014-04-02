#pragma once
class SoundMan
{
private:
	std::map<std::string, sf::SoundBuffer> sndMap;
	sf::Sound playable[32];
	bool playing[32];
	void checkPlaying();
	int getFreeChannel();
public:
	void addSound(std::string name, std::string path);
	void playPowSound(int id);
	void playBlockBreakSound();
	void playPowDeactivationSound(int id);
	void playGameStartSound();
	void playButtonSound();
	void playLifeLostSound();
	void playGameOverSound();
	void playSoundFromName(std::string name);
	SoundMan();
	~SoundMan();
};

