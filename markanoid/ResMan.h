#pragma once
class ResMan
{
	std::vector<std::string> tPaths;
	std::map<std::string, sf::Texture*> textPStor;
	std::map<std::string, sf::Music*> musicPStor;
	std::map<std::string, sf::Sound*> soundPStor;
public:
	ResMan()
	{

	}

	bool addTexture(std::string path)
	{
		sf::Texture* _tmp = new sf::Texture();
		if (!_tmp->loadFromFile(path))
		{
			delete _tmp;
			return false;
		}
		else
		{
			tPaths.emplace_back(path);
			textPStor[path] = _tmp;
			return true;
		}
	}

	bool addMusic(std::string path)
	{
		sf::Music* _tmp = new sf::Music();
		if (!_tmp->openFromFile(path)) return false;
		musicPStor[path] = _tmp;
	}

	sf::Music* getMusic(std::string id)
	{
		return musicPStor[id];
	}

	sf::Texture* getTexture(std::string id)
	{
		return textPStor[id];
	}

	~ResMan()//TODO: create a way to delete the memory of all texture pointers in the map
	{
		for (int i = 0; i < tPaths.size(); i++)
		{
			std::cout << tPaths.at(i) << std::endl;
			delete textPStor[tPaths.at(i)];
		}
		textPStor.clear();
		tPaths.clear();
	}
};

