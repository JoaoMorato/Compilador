#include <fstream>
#include <string>
#include "ControlFile.hpp"


//char character = 0;

ControlFile::ControlFile(){}

ControlFile::ControlFile(std::string _file) {
	file.open(_file);
	if (!file.is_open())
		throw "Nao foi possivel encontrar o arquivo.";

	//outFile.open(_file + ".out", )
}

bool ControlFile::ReadNext() {
	if (!file.is_open() || end)
		return false;

	character = file.get();

	if (character == -1)
		end = true;

	return true;
}

void ControlFile::Close() {
	if (file.is_open())
		file.close();
}

void ControlFile::Reset() {
	if (!file.is_open())
		return;

	file.clear();
	file.seekg(0);
	end = false;
}