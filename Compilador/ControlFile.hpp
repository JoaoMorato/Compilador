#ifndef _CONTROL_FILE_
#define _CONTROL_FILE_
#pragma once

#include <fstream>
#include <string>

class ControlFile {
private:
	std::ifstream file;
	std::ofstream outFile;

public:
	char character = 0;

	ControlFile();
	ControlFile(std::string _file);

	void MoveNext();
	bool ReadNext();
	void Close();
};

#endif // !_CONTROL_FILE_
