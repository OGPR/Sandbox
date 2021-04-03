#ifndef FILEREADER__H
#define FILEREADER__H
#include <fstream>
#include <map>

void readFile(std::string fileName, std::map<std::string, unsigned long>& parameterMap);



#endif // !FILEREADER__H
