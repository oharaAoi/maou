#include "LoadFile.h"

void LoadFile::Init() {
	///ファイルの作成
	const std::string kScorePath = "./TimeScore/";;
	filePath = kScorePath + "timeScore.json";

	json  timeDate;

	hiScore = "hiScore";
	secondScore = "secondScore";
	thirdScore = "thirdScore";

	std::ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		inputFile >> timeDate;
		inputFile.close();
	} else {
		if (!timeDate.contains(hiScore)) {
			timeDate[hiScore] = { {"time", 999} };
		}

		if (!timeDate.contains(secondScore)) {
			timeDate[secondScore] = { {"time", 999} };
		}

		if (!timeDate.contains(thirdScore)) {
			timeDate[thirdScore] = { {"time", 999} };
		}

		std::ofstream outputFile(filePath);
		if (outputFile.is_open()) {
			outputFile << std::setw(4) << timeDate << std::endl;
			outputFile.close();
		} else {
			std::cerr << "ファイルを開けませんでした。" << std::endl;
		}
	}
}

void LoadFile::WriteFile(int count) {
	json scoreData;

	std::ifstream inputFile(filePath);
	if (inputFile.is_open()) {
		inputFile >> scoreData;
		inputFile.close();
	}

	if (scoreData[hiScore]["time"] > count) {
		scoreData[hiScore]["time"] = count;

	} else if (scoreData[secondScore]["time"] > count) {
		scoreData[secondScore]["time"] = count;

	} else if (scoreData[thirdScore]["time"] > count) {
		scoreData[thirdScore]["time"] = count;
	}

	// ファイルに更新されたJSONデータを書き込む
	std::ofstream outputFile(filePath);
	if (outputFile.is_open()) {
		outputFile << std::setw(4) << scoreData << std::endl;
		outputFile.close();
	} else {
		std::cerr << "ファイルを開けませんでした。" << std::endl;
	}
}