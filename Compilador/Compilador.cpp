#include "Tokens.hpp"
#include "ControlFile.hpp"
#include "Analise.hpp"

#include <iostream>
#include <vector>
#include <tuple>

void Sintatica(ControlFile& c) {
	std::string txt = "";
	long line = 1;
	while (c.ReadNext()) {
		if (c.character == '\n') {
			txt += c.character;

			int col = AnaliseLexica(txt);
			if (col) {
				printf("Token nao reconhecido (%lu, %i)\r\n", line, col);
			}
			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
	}
}

void Lexica(ControlFile& c) {
	std::string txt = "";
	long line = 1;
	while (c.ReadNext()) {
		if (c.character == '\n') {
			txt += c.character;

			int col = AnaliseLexica(txt);
			if (col) {
				printf("Token nao reconhecido (%lu, %i)\r\n", line, col);
			}
			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
	}
}

int main() {
	std::string file = "F:\\Projetos\\Compilador\\Compilador\\SIMPLE.txt"; // Insira o nome do arquivo aqui

	ControlFile c = ControlFile(file);

	Lexica(c);
	c.Reset();
	Sintatica(c);
	c.Reset();


	c.Close();
}

