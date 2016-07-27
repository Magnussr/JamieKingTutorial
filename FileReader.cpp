#include "FileReader.h"
#include <iostream>
#include <fstream>

std::string FileReader::readShaderCode(const char* fileName)
{
	std::ifstream input(fileName);
	if (!input.good())
	{
		std::cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
}