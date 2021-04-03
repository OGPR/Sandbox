#include "FileReader.h"
#include <string>
#include <algorithm>

void readFile(std::string fileName, std::vector<unsigned long>& parameters )
{
    std::ifstream inputFile;

    inputFile.open(fileName, std::ios::in);

    if (inputFile.fail())
    {
        throw std::runtime_error(fileName + " not successfully opened - does it exist?");
    }

    std::string line;
    while (getline(inputFile, line))
    {
        auto it = std::find(std::begin(line), std::end(line), '=');
        std::string valueAsString(++it, std::end(line));
        parameters.push_back(std::stoul(valueAsString));
    }

    inputFile.close();
}
