#include "Tokens.hpp"
#include "ControlFile.hpp"
#include "Analise.hpp"

#include <iostream>
#include <vector>
#include <tuple>

bool Semantica(ControlFile& c) {
	int line = 1;
	int line2 = -1;
	bool ok = true;
	std::string txt = "";

	while (c.ReadNext()) {
		if (c.character == '\n' || c.character == -1) {
			if (c.character == -1)
				txt += " EOF";
			else
				txt += c.character;

			int l = AnaliseSemantica(line, line2, txt);

			if (l <= line2)
				ok = false;
			else line2 = l;

			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
	}

	if (!txt.empty())
		ok = AnaliseSemantica(line, line2, txt) > line2 && ok;

	return ok;
}

bool Sintatica(ControlFile& c) {
	std::string txt = "";
	long line = 1;
	bool ok = true;
	while (c.ReadNext()) {
		if (c.character == '\n' || c.character == -1) {
			if (c.character == -1)
				txt += " EOF";
			else
				txt += c.character;

			ok = AnaliseSintatica(line, txt) && ok;

			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
	}

	if (!txt.empty())
		ok = AnaliseLexica(line, txt) && ok;

	if (!Token::end)
		printf("ERRO: Token 'end' nao encontrado. (%i, 1)\r\n", line);

	return ok && Token::end;
}

bool Lexica(ControlFile& c) {
	std::string txt = "";
	long line = 1;
	bool ok = true;
	while (c.ReadNext()) {
		if (c.character == '\n' || c.character == -1) {
			if (c.character == -1)
				txt += " EOF";
			else
				txt += c.character;

			ok = AnaliseLexica(line, txt) && ok;

			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
	}

	if (!txt.empty())
		ok = AnaliseLexica(line, txt) && ok;
	return ok;
}

int main() {
	std::string file = "F:\\Projetos\\Compilador\\Compilador\\SIMPLE.txt"; // Insira o nome do arquivo aqui

	ControlFile c = ControlFile(file);
	bool ok = true;

	Token t;

	ok = Lexica(c) && ok;
	c.Reset();
	printf("\r\n");
	ok = Sintatica(c) && ok;
	c.Reset();
	printf("\r\n");
	ok = Semantica(c) && ok;
	printf("\r\n");

	c.Close();
	if (ok)
		printf("Execucao terminada com sucesso.");
	else
		printf("Execucao terminada com erro(s).");
}

