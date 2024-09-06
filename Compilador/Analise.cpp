#include "Tokens.hpp"
#include <string>
#include <vector>
#include <tuple>

std::string ValidaToken(int value, std::string str, int lastToken) {
	switch (value) {
	case 41:
		//if()
		break;
	}

	return "";
}

void AnaliseSintatica(int line, std::string linha) {
	Token t;
	std::string str = "";
	int posi = 0;
	int coluna = 1;
	bool label = false;
	std::vector<int> lista;

	while (posi < linha.length()) {
		if (linha[posi] == '\r') {
			posi++;
			continue;
		}

		if (linha[posi] == ' ') {
			posi++;
			if (str.empty()) {
				coluna++;
				continue;
			}

			int value = t.GetToken(str);

			int lastToken = 0;

			if (lista.size() > 0)
				lastToken = lista.back();

			auto result = ValidaToken(value, str, lastToken);

			if (!result.empty()) {
				printf("%s (%i, %i)\r\n", result.c_str(), line, coluna);
				return;
			}

			int token = t.CheckVariables(str);

			lista.push_back(value);
			coluna += str.length() + 1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty()) {
			if (!t.GetToken(str))
				return;

			coluna += str.length();
			str.clear();
			continue;
		}

		str += linha[posi];
		posi++;
	}

	if (!str.empty()) {
		if (!t.GetToken(str))
			return;
	}
}

void AnaliseLexica(int line, std::string linha) {
	Token t;
	std::string str = "";
	int posi = 0;
	int coluna = 1;
	bool fim = false;

	while (posi < linha.length()) {
		if (linha[posi] == '\r') {
			posi++;
			continue;
		}

		if (linha[posi] == ' ') {
			posi++;
			if (str.empty()) {
				coluna++;
				continue;
			}

		jmp:
			int value = t.GetToken(str);

			if (!value) {
				printf("Token nao reconhecido '%s'. (%i, %i)\n", str.c_str(), line, coluna);
				return;
			}

			int token = t.CheckVariables(str);

			if (value == 51 || (token == -1 && value == 41))
				token = t.RegisterVariable(str);

			if (token == -1)
				printf("[%i,  , (%i, %i)\n", value, line, coluna);
			else
				printf("[%i, %i, (%i, %i)\n", value, token, line, coluna);

			coluna += str.length() + 1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty())
			goto jmp;

		str += linha[posi];
		posi++;
	}

	if (str == "\r\n" || str == "\n") {
		printf("[10,  , (%i, %i)\n", line, coluna);
		return;
	}

	if (fim)
		printf("Token de fim de linha nao encontrado");
}