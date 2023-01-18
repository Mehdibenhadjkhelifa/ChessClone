
#include <fstream>
#include <sstream>
#include <iostream> //this should get removed later

#include "RendererData.h"




void RendererData::AssignPosInLine(float InitialX, float InitialY, Line* line)
{
    for (int i = 0;i < 18;i++)
    {
        if (i % 2)
            line->posInLine[i] = InitialY;
        else
            line->posInLine[i] = InitialX + (0.25f * (i / 2));

    }
}

void RendererData::AssignIndexToTile(unsigned int InitialIndex, unsigned int* Data, unsigned int& DataIndex)
{
    for (int i = 1;i < 9;i++)
    {
        Data[DataIndex] = InitialIndex + i - 1;
        Data[DataIndex + 1] = InitialIndex + i;
        Data[DataIndex + 2] = InitialIndex + i + 9;
        Data[DataIndex + 3] = InitialIndex + i + 9;
        Data[DataIndex + 4] = InitialIndex + i + 9 - 1;
        Data[DataIndex + 5] = InitialIndex + i - 1;

        DataIndex += 6;
    }
}

void RendererData::BindData(Line* BoardData, unsigned int* DataIndex)
{
    float BuildingX = -1.f;
    float BuildingY = -1.f;


    for (int i =0;i<9;i++)
    {

        AssignPosInLine(BuildingX, BuildingY, (BoardData+i));
        BuildingY += 0.25f;

    }

    unsigned int StartingIndex = 0;

    for (int i = 0;i < 8; i++)
    {
        AssignIndexToTile(i * 9, DataIndex, StartingIndex);


    }

}

const std::tuple<std::string, std::string, std::string> RendererData::ParseShader(const std::filesystem::path& filePath) 
{
    std::ifstream stream(filePath);
    std::stringstream ss[3];
    std::string line;

    if (!stream)
        std::cout << "Error: Wrong filePath" << std::endl;

    enum class ShaderTYPE
    {
        NONE = -1,
        VERTEX = 0,
        WHITEFRAGMENT = 1,
        BLACKFRAGMENT = 2
    };

    ShaderTYPE type = ShaderTYPE::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderTYPE::VERTEX;
            else if (line.find("whiteFragment") != std::string::npos)
                type = ShaderTYPE::WHITEFRAGMENT;
            else if (line.find("blackFragment") != std::string::npos)
                type = ShaderTYPE::BLACKFRAGMENT;

        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return std::make_tuple(ss[0].str(), ss[1].str(), ss[2].str());

}

/// 
/// This is a function to resolve the Paths issue that occurs
/// when one tries to specify a path from the project directory 
/// 
/// \returns relative Path to the specified path wether no matter the working directory (project or output)
/// 
std::filesystem::path RendererData::GetFilePath(const std::filesystem::path& TargetPath)
{
    if (std::filesystem::relative(TargetPath) != "") // meaning we are in the working directory of the project
        return TargetPath;
    else
        return std::filesystem::path("../../../ChessClone/" + TargetPath.generic_string());

}

