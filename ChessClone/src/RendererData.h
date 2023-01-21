#pragma once
#include <tuple>
#include <string>
#include <filesystem>


struct Line
{
	float posInLine[18];
};

class RendererData
{
public:
	static void AssignPosInLine(float InitialX, float InitialY, Line* line);
	static void AssignIndexToTile(unsigned int InitialIndex, unsigned int* Data, unsigned int& DataIndex);
	static void BindData(Line* BoardData, unsigned int* DataIndex);


	static const std::tuple<std::string, std::string, std::string> ParseShader(const std::filesystem::path& filePath);
	static std::filesystem::path GetFilePath(const std::filesystem::path& TargetPath);
};