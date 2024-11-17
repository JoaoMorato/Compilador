#include "GeradorSML.hpp"
#include "Tokens.hpp"
#include <fstream>
#include <list>

std::vector<std::tuple<int, std::string>> valores;


std::tuple<int, std::string> Next() {
	if (valores.size() == 0)
		return { 0, "" };
	auto a = *valores.rbegin();
	valores.pop_back();
	return a;
}

int Variavel(std::list<std::tuple<std::string, int>>& a, std::string value) {
	int num = -1;
	for (auto i = a.begin(); i != a.end(); i++) {
		if (std::get<0>(*i) == value)
			return num;
		num--;
	}
	a.push_back({ value, num });
	return num;
}

int Label(std::list<std::tuple<std::string, int>>& a, std::string value) {
	int num = -1001;
	for (auto i = a.begin(); i != a.end(); i++) {
		if (std::get<0>(*i) == value)
			return num;
		num--;
	}
	a.push_back({ value, num });
	return num;
}

void WriteFile(std::list<std::tuple<int, int>> lista, const char* file) {
	FILE* f;
	fopen_s(&f, file, "w");
	if (f == 0)
		return;
	for (auto i : lista) {
		char buff[6] = { 0 };
		int p0 = std::get<0>(i);
		int p1 = std::get<1>(i);
		if (p0 != 0)
			std::snprintf(buff, 6, "+%02i%02i", p0, p1);
		else if (p1 < 0)
			std::snprintf(buff, 6, "-%04i", p1 * -1);
		else
			std::snprintf(buff, 6, "+%04i", p1);

		fwrite(buff, 1, 5, f);
		fwrite("\n", 1, 1, f);
	}
	fclose(f);
}

std::list<std::vector<std::tuple<int, std::string>>> Otimizar(std::list<std::vector<std::tuple<int, std::string>>> lista) {
	for (auto it = lista.begin(); it != lista.end(); it++) {
		auto v = *it;
		auto copia = it;
		std::vector<std::string> labels;
		for (auto it2 = ++copia; it2 != lista.end(); it2++) {
			auto v2 = *it2;
			if (v2.size() != v.size()) break;
			bool igual = true;
			for (int i = 1; i < v2.size(); i++) {
				if (std::get<0>(v2[i]) != std::get<0>(v[i]) || std::get<1>(v2[i]) != std::get<1>(v[i])) {
					igual = false;
					break;
				}
			}
			if (igual) {
				labels.push_back(std::get<1>(v2[0]));
				it2 = lista.erase(it2);
				it2--;
			}
		}
		if (labels.size()) {
			for (auto a = lista.begin(); a != lista.end(); a++) {
				int anterior = 0;
				for (auto b = a->begin(); b != a->end(); b++) {
					if (anterior != 65) {
						anterior = std::get<0>(*b);
						continue;
					}
					auto str = std::get<1>(*b);
					for (auto c : labels) {
						if (c != str) continue;
						*b = { std::get<0>(*b), std::get<1>(v[0]) };
						break;
					}
				}
			}
		}
	}

	return lista;
}

void GerarSML(const char* file) {
	//std::ofstream stream(file);
	//if (!stream.is_open())
	//	throw "Nao pode abrir arquivo " + std::string(file);

	std::list<std::tuple<std::string, int>> numLine;
	std::list<std::tuple<std::string, int>> label;
	auto tokens = Otimizar(Token::tokensRegisted);
	std::list<std::tuple<std::string, int>> variaveis;

	std::list<std::tuple<int, int>> codigo;

	while (!tokens.empty()) {
		valores = *tokens.begin();
		tokens.pop_front();
		int count = 0;
		auto labelR = valores.begin();
		numLine.push_back({ std::get<1>(*labelR), codigo.size() });
		valores.erase(labelR);
		std::string aux = "";
		std::string _gt = "";
		while (true) {
			auto a = Next();
			if (std::get<0>(a) == 0)
				break;
			int code = std::get<0>(a);
			switch (code) {
			case 41:
			case 51:
			{
				auto b = Next();
				if (std::get<0>(b) == 65) {
					_gt = std::get<1>(a);
					a = Next();
					if (std::get<0>(a) == 0)
						valores.push_back(b);
					else valores.push_back(a);
					break;
				}
				valores.push_back(b);
				aux = std::get<1>(a);
			}
			break;
			case 11:
			igual:
				if (aux != "")
					codigo.push_back({ 20, Variavel(variaveis, aux) });
				break;
			case 21:
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				a = Next();
				codigo.push_back({ 30, Variavel(variaveis, std::get<1>(a)) });
				aux = "";
				break;
			case 22:
				a = Next();
				if (std::get<0>(a) == 11) {
					try {
						int _ = atoi(aux.c_str());
						aux = "-" + aux;
					}
					catch (std::exception ex) {
					}
					goto igual;
				}
				codigo.push_back({ 20, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 31, Variavel(variaveis, aux) });
				aux = "";
				break;
			case 23:
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				a = Next();
				codigo.push_back({ 33, Variavel(variaveis, std::get<1>(a)) });
				aux = "";
				break;
			case 24:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 32, Variavel(variaveis, aux) });
				aux = "";
				break;
			case 25:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 34, Variavel(variaveis, aux) });
				aux = "";
				break;
			case 31:
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				a = Next();
				codigo.push_back({ 31, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 42, Label(label, _gt) });
				aux = "";
				break;
			case 32:
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				a = Next();
				codigo.push_back({ 31, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 42, codigo.size() + 2 });
				codigo.push_back({ 40, Label(label, _gt) });
				aux = "";
				break;
			case 33:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				codigo.push_back({ 31, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 41, Label(label, _gt) });
				aux = "";
				break;
			case 34:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 31, Variavel(variaveis, aux) });
				codigo.push_back({ 41, Label(label, _gt) });
				aux = "";
				break;
			case 35:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, aux) });
				codigo.push_back({ 31, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 41, Label(label, _gt) });
				codigo.push_back({ 42, Label(label, _gt) });
				aux = "";
				break;
			case 36:
				a = Next();
				codigo.push_back({ 20, Variavel(variaveis, std::get<1>(a)) });
				codigo.push_back({ 31, Variavel(variaveis, aux) });
				codigo.push_back({ 41, Label(label, _gt) });
				codigo.push_back({ 42, Label(label, _gt) });
				aux = "";
				break;
			case 62:
				codigo.push_back({ 10, Variavel(variaveis, aux) });
				break;
			case 63:
				codigo.push_back({ 21, Variavel(variaveis, aux) });
				break;
			case 64:
				codigo.push_back({ 11, Variavel(variaveis, aux) });
				break;
			case 65:
				codigo.push_back({ 40, Label(label, _gt) });
				break;
			case 67:
				codigo.push_back({ 43, 0 });
				break;
			}
			count++;
		}
	}
	int limite = codigo.size();
	for (auto i : variaveis) {
		int posi = codigo.size();
		try {
			int num = atoi(std::get<0>(i).c_str());
			codigo.push_back({ 0, num });
		}
		catch (std::exception ex) {
			codigo.push_back({ 0, 0 });
		}
		int j = 0;
		for (auto h = codigo.begin(); j < limite; j++, h++) {
			if (std::get<1>(*h) != std::get<1>(i)) continue;

			*h = { std::get<0>(*h), posi };
		}
	}
	int j = 0;
	for (auto h = codigo.begin(); j < limite; j++, h++) {
		if (std::get<1>(*h) > -999) continue;

		for (auto i : label) {
			if (std::get<1>(i) != std::get<1>(*h)) continue;
			for (auto b : numLine) {
				if (std::get<0>(b) != std::get<0>(i)) continue;
				*h = { std::get<0>(*h), std::get<1>(b) };
				break;
			}
			break;
		}
	}

	WriteFile(codigo, file);
}

