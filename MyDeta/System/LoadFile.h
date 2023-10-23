#pragma once
#include <json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

class LoadFile
{

private:

	std::string filePath;

	std::string hiScore;
	std::string secondScore;
	std::string thirdScore;

public:

	void Init();

	void WriteFile(float count);

	void LoadJsonFile(float* time);

};

