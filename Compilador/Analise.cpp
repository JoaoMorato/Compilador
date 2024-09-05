#include "Tokens.hpp"
#include <string>
#include <vector>
#include <tuple>

std::string AnaliseSintatica(std::vector<std::tuple<int, std::string>> lista) {
	
}

int AnaliseLexica(std::string linha) {
	Token t;
	std::string str = "";
	int posi = 0;
	int coluna = 1;

	std::vector<std::tuple<int, std::string>> lista;

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
			int token = t.GetToken(str);
			if (!token)
				return coluna;

			lista.push_back({ token, str });

			coluna += str.length() + 1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty()) {
			if (!t.GetToken(str))
				return coluna;

			coluna += str.length();
			str.clear();
			continue;
		}

		str += linha[posi];
		posi++;
	}

	if (!str.empty()) {
		if (!t.GetToken(str))
			return coluna;
	}

	return 0;
}

//int AnaliseSintatica(std::string linha, int num, int line, std::vector<std::string>& _tokens) {
//	bool label = false;
//	bool falha = false;
//	int n;
//	std::string value;
//	int coluna = 1;
//	for (char c : linha) {
//		if (!label) {
//			if (std::isdigit(c)) {
//				value += c;
//				continue;
//			}
//
//			if (c == ' ') {
//				if (falha) {
//					printf("ERRO: Token invalido. (%i, %i)", line, coluna);
//					return -1;
//				}
//				label = true;
//				n = std::stoi(value);
//				if (n <= num) {
//					printf("ERRO: Sequencial de linha invalido. (%i, %i)", line, coluna);
//					return -1;
//				}
//				_tokens.push_back(value);
//				printf("[51, %llu, (%i, %i)]", _tokens.size() - 1, line, coluna);
//				coluna += value.length();
//				continue;
//			}
//
//			falha = true;
//		}
//		if (c == ' ' && value.length() == 0) continue;
//
//		if (c == ' ') {
//
//		}
//	}
//}