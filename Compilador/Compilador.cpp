#include <iostream>
#include <vector>
#include <tuple>
#include "ControlFile.cpp"
#include "Nodes.cpp"

ControlFile c;
std::vector<std::tuple<long long, std::string>> tokens_v;


bool Special(char c) {
	switch (c) {
		case '=':
		case '+':
		case '*':
		case '-':
		case '/':
		case '(':
		case ')':
			return true;
	}
	return false;
}

int BlankSpace(char c) {
	switch (c) {
	case ' ':
		return 1;
	case '\n':
	case '\r':
		return 2;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Nenhum arquivo passado como argumento.");
		return 1;
	}

	c = ControlFile(argv[1]);

	std::string txt = "";
	long line = -1;
	long line2 = 1;
	long column = 1;
	bool lineRead = false;
	while (c.ReadNext()) {
		if (!lineRead) {
			if (std::isdigit(c.character)) {
				txt += c.character;
				c.MoveNext();
				continue;
			}
			if (txt.empty() && BlankSpace(c.character) == 1) {
				c.MoveNext();
				column++;
				continue;
			}
			long aux = std::stoi(txt);
			if (aux <= line) {
				printf("ERRO: Numero da linha deve ser maior que a anterior. Linha anterior: %ll, linha atual: %ll [Linha: %ll; Coluna: %ll]", line, aux, aux, column);
				break;
			}
			line = aux;
			if (BlankSpace(c.character) != 1) {
				printf("ERRO:Token nao compreendido, tente separar codigo da enumeracao da linha [Linha: %ll; Coluna: %ll]", line, column);
				break;
			} else {
				c.MoveNext();
				column++;
			}
			printf("[51, %i, (%ll, %ll)]\n", line2, column);
			line2++;
			column += txt.length();
			lineRead = true;
			continue;
		}

		if (Special(c.character)) {
			if (txt.empty()) {
				printf("ERRO: Faltando expressao antes de '%c' [Linha: %ll; Coluna: %ll]", c.character, line, column);
				break;
			}
		}
		if (BlankSpace(c.character) == 1) {
			column++;
			c.MoveNext();
			continue;
		}
		char a = c.character;
		if (a >= 'A' && a <= 'Z') {
			int aux = 'A' - a;
			a = 'a' + aux;
		}
	}

	c.Close();
}

