#include <fstream>
#include <string>

class ControlFile {
private:
	std::ifstream file;
	std::ofstream outFile;

public:
	char character = 0;

	ControlFile(std::string _file) {
		file.open(_file);
		if (!file.is_open())
			throw "Nao foi possivel encontrar o arquivo.";

		//outFile.open(_file + ".out", )
	}

	void MoveNext() {
		if (!file.is_open())
			return;
		file.get();
	}


	bool ReadNext() {
		if (!file.is_open())
			return false;
		char c = file.peek();
		if (c == EOF)
			return false;

		character = c;
		return true;
	}

	void Close() {
		if (file.is_open())
			file.close();
	}
};