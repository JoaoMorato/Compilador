#include "Tokens.hpp"
#include "ControlFile.hpp"
#include "Analise.hpp"

#include <iostream>
#include <vector>
#include <tuple>

ControlFile c;
//std::vector<std::tuple<long long, std::string>> tokens_v;
//std::vector<int> label;

int main() {
	std::string file = "F:\\Projetos\\Compilador\\Compilador\\SIMPLE.txt"; // Insira o nome do arquivo aqui

	c = ControlFile(file);

	std::string txt = "";
	long line = 1;
	//long line2 = 1;
	//long column = 1;
	//bool lineRead = false;
	while (c.ReadNext()) {
		if (c.character == '\n') {
			txt += c.character;
			c.MoveNext();
			
			int col = AnaliseLexica(txt);
			if (col) {
				printf("Token nao reconhecido (%lu, %i)\r\n", line, col);
			}
			line++;
			txt.clear();
			continue;
		}

		txt += c.character;
		c.MoveNext();

		/*if (!lineRead) {
			if (std::isdigit(c.character)) {
				txt += c.character;
				c.MoveNext();
				continue;
			}
			if (txt.empty() && ) {
				c.MoveNext();
				column++;
				continue;
			}
			long aux = std::stoi(txt);
			if (aux <= line) {
				printf("ERRO: Numero da linha deve ser maior que a anterior. Linha anterior: %ll, linha atual: %ll [Linha: %ll, Coluna: %ll]", line, aux, aux, column);
				break;
			}
			line = aux;
			if (BlankSpace(c.character) != 1) {
				printf("ERRO:Token nao compreendido, tente separar codigo da enumeracao da linha [Linha: %ll, Coluna: %ll]", line, column);
				break;
			} else {
				c.MoveNext();
				column++;
			}
			printf("[51, %i, (%ll, %ll)]\n", line2, line2, column);
			line2++;
			column += txt.length();
			lineRead = true;
			continue;
		}

		if (Special(c.character)) {
			if (txt.empty()) {
				printf("ERRO: Faltando expressao antes de '%c' [Linha: %ll, Coluna: %ll]", c.character, line, column);
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
		}*/
	}

	c.Close();
}

