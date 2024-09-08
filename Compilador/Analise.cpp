#include "Tokens.hpp"
#include <string>
#include <vector>
#include <tuple>

std::string ValidaToken(int value, std::string str, int lastToken) {
	switch (value) {
	case 41:
		if (lastToken == 62 || lastToken == 63) {
			if (Token::CheckVariables(str) < 0)
				Token::RegisterVariable(str);
			Token::InitVariable(str);
			break;
		}
		if (!Token::VariableInited(str))
			return "Token nao inicializado.";
		break;
	case 51:
		if (lastToken == 65 && !Token::CheckVariables(str))
			return "Label nao registrado.";
		break;
	}

	return "";
}

bool AnalisarSequenciaToken(std::vector<std::tuple<int, int>> lista, int line) {
	while (lista.size() > 1) {
		auto aux = lista[lista.size() - 1];
		int a = std::get<0>(aux);
		int b = 0;
		int c = 0;
		lista.pop_back();
		int result = Token::CheckTokens(a);

		if (result == 100 && lista.size()) {
			aux = lista[lista.size() - 1];
			b = std::get<0>(aux);
			lista.pop_back();

			result = Token::CheckTokens(b, a);
		}

		if (lista.size() && result == 100) {
			auto h = lista[lista.size() - 1];
			c = std::get<0>(h);
			lista.pop_back();

			result = Token::CheckTokens(c, b, a);
		}

		if (a == 67 || b == 67 || c == 67)
			Token::end = true;

		if (result == 100) {
			printf("ERRO: Expressao nao compreendida. (%i, %i)\r\n", line, std::get<1>(aux));
			return false;
		}

		if (result)
			lista.push_back({ result, std::get<1>(aux) });
	}

	return true;
}

int AnaliseSemantica(int line, int oldLine, std::string linha) {
	std::string str = "";
	int posi = 0;
	int coluna = 1;
	int currentLine = 0;
	bool label = false;
	int oldValue = 0;
	// 0 letra, 1 num, 2 especial
	int tipo = -1;

	while (posi < linha.length()) {
		if (linha[posi] == '\r') {
			posi++;
			continue;
		}

		if (linha[posi] == ' ') {
			posi++;
			if (str.empty())
				continue;

		jmp:
			int value = Token::GetToken(str);

			if (value == 51 && !label) {
				currentLine = atoi(str.c_str());
				label = true;

				if (currentLine < 0)
					printf("ERRO: Label nao pode ser negativa, valor atual '%i'. (%i, %i)\r\n", currentLine, line, coluna);
				else if (currentLine <= oldLine)
					printf("ERRO: Label deve ser maior que seu antecessor. Valor atual '%i', valor anterior '%i'. (%i, %i)\r\n", currentLine, oldLine, line, coluna);
			} else if (oldValue == 65 && value == 51) {
				if (!Token::VariableInited(str))
					printf("ERRO: Label '%s' nao encontrada. (%i, %i)\n\r", str.c_str(), line, coluna);
			}

			oldValue = value;

			if (value == 61)
				return currentLine;

			coluna = posi + 1;
			tipo = -1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty())
			goto jmp;

		char c = linha[posi];
		switch (tipo) {
		case -1:
			if (c >= 'a' && c <= 'z')
				tipo = 0;
			else if (std::isdigit(c))
				tipo = 1;
			else tipo = 2;
			break;
		case 0:
			if (c < 'a' || c > 'z')
				goto jmp;
			break;
		case 1:
			if (!std::isdigit(c))
				goto jmp;
			break;
		case 2:
			if (std::isdigit(c) || (c >= 'a' && c <= 'z'))
				goto jmp;
		}


		str += linha[posi];
		posi++;
	}

	if (!str.empty()) {
		int value = Token::GetToken(str);

		if (value == 51 && !label) {
			currentLine = atoi(str.c_str());
			label = true;

			if (currentLine <= oldLine)
				printf("ERRO: Label deve ser maior que seu antecessor. (%i, %i)", line, coluna);
		} else if (oldValue == 65 && value == 51) {
			if (!Token::VariableInited(str))
				printf("ERRO: Label nao encontrada. (%i, %i)", line, coluna);
		}
	}

	return currentLine;
}

bool AnaliseSintatica(int line, std::string linha) {
	std::string str = "";
	int posi = 0;
	int coluna = 1;
	bool label = false;
	std::vector<std::tuple<int, int>> lista;
	// 0 letra, 1 num, 2 especial
	int tipo = -1;

	while (posi < linha.length()) {
		if (linha[posi] == '\r') {
			posi++;
			continue;
		}

		if (linha[posi] == ' ') {
			posi++;
			if (str.empty())
				continue;
		jmp:
			int value = Token::GetToken(str);

			if (value == 51 && !label) {
				label = true;
				Token::InitVariable(str);
			}

			if (!label) {
				printf("ERRO: Label nao compreendido ou faltando. (%i, %i)\r\n", line, coluna);
				return false;
			}

			int lastToken = 0;

			if (lista.size() > 0)
				lastToken = std::get<0>(lista.back());

			auto result = ValidaToken(value, str, lastToken);

			if (!result.empty()) {
				printf("ERRO: %s (%i, %i)\r\n", result.c_str(), line, coluna);
				return false;
			}

			int token = Token::CheckVariables(str);

			lista.push_back({ value, coluna });
			tipo = -1;
			coluna = posi + 1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty())
			goto jmp;

		char c = linha[posi];
		switch (tipo) {
		case -1:
			if (c >= 'a' && c <= 'z')
				tipo = 0;
			else if (std::isdigit(c))
				tipo = 1;
			else tipo = 2;
			break;
		case 0:
			if (c < 'a' || c > 'z')
				goto jmp;
			break;
		case 1:
			if (!std::isdigit(c))
				goto jmp;
			break;
		case 2:
			if (std::isdigit(c) || (c >= 'a' && c <= 'z'))
				goto jmp;
		}

		str += linha[posi];
		posi++;
	}

	if (!str.empty()) {
		int a = Token::GetToken(str);
		int lastToken = 0;

		if (lista.size() > 0)
			lastToken = std::get<0>(lista.back());

		auto result = ValidaToken(a, str, lastToken);

		if (!result.empty()) {
			printf("ERRO: %s (%i, %i)\r\n", result.c_str(), line, coluna);
			return false;
		}

		lista.push_back({ a, coluna });
	}

	return AnalisarSequenciaToken(lista, line);
}

bool AnaliseLexica(int line, std::string linha) {
	std::string str = "";
	int posi = 0;
	int coluna = 1;
	bool comentario = false;
	// 0 letra, 1 num, 2 especial
	int tipo = -1;

	while (posi < linha.length()) {
		if (linha[posi] == '\r') {
			posi++;
			continue;
		}

		if (linha[posi] == ' ') {
			posi++;
			if (str.empty())
				continue;

		jmp:
			int value = Token::GetToken(str);

			int token = Token::CheckVariables(str);

			if (comentario && value != 10)
				goto jmp2;

			if (!value) {
				printf("ERRO: Token nao reconhecido '%s'. (%i, %i)\r\n", str.c_str(), line, coluna);
				return false;
			}

			if (value == 51 || (token == -1 && value == 41))
				token = Token::RegisterVariable(str);

			if (token == -1)
				printf("[%02i,  , (%02i, %02i)]\r\n", value, line, coluna);
			else
				printf("[%02i, %i, (%02i, %02i)]\r\n", value, token, line, coluna);

			if (value == 61)
				comentario = true;

		jmp2:
			tipo = -1;
			coluna = posi + 1;
			str.clear();
			continue;
		}

		if (linha[posi] == '\n' && !str.empty())
			goto jmp;

		char c = linha[posi];
		switch (tipo) {
		case -1:
			if (c >= 'a' && c <= 'z')
				tipo = 0;
			else if (std::isdigit(c))
				tipo = 1;
			else tipo = 2;
			break;
		case 0:
			if (c < 'a' || c > 'z')
				goto jmp;
			break;
		case 1:
			if (!std::isdigit(c))
				goto jmp;
			break;
		case 2:
			if (std::isdigit(c) || (c >= 'a' && c <= 'z'))
				goto jmp;
		}

		str += linha[posi];
		posi++;
	}

	if (!str.empty()) {
		int value = Token::GetToken(str);

		if (!value) {
			printf("ERRO: Token nao reconhecido '%s'. (%i, %i)\r\n", str.c_str(), line, coluna);
			return false;
		}

		int token = Token::CheckVariables(str);

		if (value == 51 || (token == -1 && value == 41))
			token = Token::RegisterVariable(str);

		if (token == -1)
			printf("[%02i,  , (%02i, %02i)]\r\n", value, line, coluna);
		else
			printf("[%02i, %i, (%02i, %02i)]\r\n", value, token, line, coluna);
	}

	return true;
}