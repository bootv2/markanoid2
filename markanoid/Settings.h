#pragma once
class Settings
{
	std::vector<std::string> lines;
	int windowWidth, windowHeight, maxFPS;
	float paddleVelocity, ballVelocity, powContainerVelocity;
	FileIO settingsFile;
	std::stringstream ss;
	
public:
	Settings()
	{

	}
	
	void init()
	{
		using std::string;
		string tmp;
		string settingName;
		string settingVal;

		//boost::tokenizer()

		std::cout << "constructing settings class\n";

		settingsFile.init("settings.ini");
		for (int i = 0; i < settingsFile.amountOfLines(); i++)
		{
			tmp = settingsFile.readLine(i).at(0);
			if (tmp.compare("#") == 0)
			{
				std::cout << "line " << i << " ignored: " << settingsFile.readLine(i) << std::endl;
			}
			else lines.emplace_back(settingsFile.readLine(i));
		}
		
		for (auto& string : lines)
		{
				for (int x = 0; x < string.size(); x++)
				{
					settingVal = string.at(x);

					if (settingVal.compare(":") == 0)
					{
						for (int y = 0; y < x; y++)
						{
							settingName += string.at(y);
						}
						settingVal = "";
						for (int y = x + 1; y < string.size(); y++)
						{
							settingVal += string.at(y);
						}
						std::cout << settingName <<" read as: " << settingVal << std::endl;
						break;
					}
				}
				ss << settingVal;
				if (settingName == "resX")
				{
					windowWidth = atoi(settingVal.c_str());
					std::cout << "windowWidth set to: " << windowWidth << " using stringstream on settingVal-> " << settingVal << std::endl;
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}
				else if (settingName == "resY")
				{
					windowHeight = atoi(settingVal.c_str());
					std::cout << "windowHeight set to: " << windowHeight << " using stringstream on settingVal-> " << settingVal << std::endl;
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}

				else if (settingName == "maxFPS")
				{
					maxFPS = atoi(settingVal.c_str());
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}

				else if (settingName == "paddleVelocity")
				{
					paddleVelocity = atof(settingVal.c_str());
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}

				else if (settingName == "ballVelocity")
				{
					ballVelocity = atof(settingVal.c_str());
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}

				else if (settingName == "powContainerVelocity")
				{
					powContainerVelocity = atof(settingVal.c_str());
					ss.clear();
					settingName.clear();
					settingVal.clear();
				}
				
			}
	}
	int getWindowWidth()
	{
		std::cout << windowWidth << std::endl;
		return windowWidth;
	}
	int getWindowHeight()
	{
		std::cout << windowHeight << std::endl;
		return windowHeight;
	}
	int getMaxFPS()
	{
		return maxFPS;
	}
	float getPaddleVelocity()
	{
		return paddleVelocity;
	}
	float getBallVelocity()
	{
		return ballVelocity;
	}
	float getPowContFallSpeed()
	{
		return powContainerVelocity;
	}
	void setVelocities(float vel1, float vel2, float vel3)
	{
		ballVelocity = vel1;
		paddleVelocity = vel2;
		powContainerVelocity = vel3;
	}
	void saveSettings()
	{
		settingsFile.writeString("#gameProperties\n");
		settingsFile.writeString("resX:" + std::to_string(windowWidth) + "\n");
		settingsFile.writeString("resY:" + std::to_string(windowHeight) + "\n");
		settingsFile.writeString("maxFPS:" + std::to_string(maxFPS) + "\n");
		settingsFile.writeString("\n");
		settingsFile.writeString("#difficultyBlock\n");
		settingsFile.writeString("paddleVelocity:" + std::to_string(paddleVelocity) + "\n");
		settingsFile.writeString("ballVelocity:" + std::to_string(ballVelocity) + "\n");
		settingsFile.writeString("powContainerVelocity:" + std::to_string(powContainerVelocity) + "\n");
		settingsFile.closeFile();
	}
};

