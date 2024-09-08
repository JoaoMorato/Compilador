#include "Tokens.hpp"

#include <tuple>
#include <list>
#include <string>

std::list<std::tuple<std::string, int>> Token::tokens = {
	{"\r\n", 10},
	{"\n", 10},
	{"EOF", 3},
	{"=", 11},
	{"+", 21},
	{"-", 22},
	{"*", 23},
	{"/", 24},
	{"%", 25},
	{"==", 31},
	{"!=", 32},
	{">", 33},
	{"<", 34},
	{">=", 35},
	{"<=", 36},
	{"a", 41},
	{"b", 41},
	{"c", 41},
	{"d", 41},
	{"e", 41},
	{"f", 41},
	{"g", 41},
	{"h", 41},
	{"i", 41},
	{"j", 41},
	{"k", 41},
	{"l", 41},
	{"m", 41},
	{"n", 41},
	{"o", 41},
	{"p", 41},
	{"q", 41},
	{"r", 41},
	{"s", 41},
	{"t", 41},
	{"u", 41},
	{"v", 41},
	{"w", 41},
	{"x", 41},
	{"y", 41},
	{"z", 41},
	{"rem", 61},
	{"input", 62},
	{"let", 63},
	{"print", 64},
	{"goto", 65},
	{"if", 66},
	{"end", 67}
};

std::list<std::tuple<int, std::tuple<int, int, int>, bool>> Token::merge = {
	// cod. retorno / ordem de valores a comparar / pode ser invertido
	{-1, {41, 21, 41}, false}, // a + a
	{-1, {41, 21, 51}, true}, // a + 1
	{-1, {51, 21, 51}, false}, // 1 + 1
	{-1, {41, 22, 41}, false}, // a - a
	{-1, {41, 22, 51}, true}, // a - 1
	{-1, {51, 22, 51}, false}, // 1 - 1
	{-1, {41, 23, 41}, false}, // a * a
	{-1, {41, 23, 51}, true}, // a * 1
	{-1, {51, 23, 51}, false}, // 1 * 1
	{-1, {41, 24, 41}, false}, // a / a
	{-1, {41, 24, 51}, true}, // a / 1
	{-1, {51, 24, 51}, false}, // 1 / 1
	{-1, {41, 25, 41}, false}, // a % a
	{-1, {41, 25, 51}, true}, // a % 1
	{-1, {51, 25, 51}, false}, // 1 % 1
	{-10, {11, 22, 41}, false}, // - a
	{-10, {11, 22, 51}, false}, // - 1
	{-2, {41, -10, 0}, false}, // a {tag: -10}
	{-2, {41, 11, -1}, false}, // a = {tag: -1}
	{-2, {41, 11, 41}, false}, // a = a
	{-2, {41, 11, 51}, false}, // a = 1
	{-3, {41, 31, 41}, false}, // a == a
	{-3, {41, 31, 51}, true}, // a == 1
	{-3, {41, 32, 41}, false}, // a != a
	{-3, {41, 32, 51}, true}, // a != 1
	{-3, {41, 33, 41}, false}, // a > a
	{-3, {41, 33, 51}, true}, // a > 1
	{-3, {41, 34, 41}, false}, // a < a
	{-3, {41, 34, 51}, true}, // a < 1
	{-3, {41, 35, 41}, false}, // a >= a
	{-3, {41, 35, 51}, true}, // a >= 1
	{-3, {41, 36, 41}, false}, // a <= a
	{-3, {41, 36, 51}, true}, // a <= 1
	{-4, {65, 51, 0}, false}, // goto 1
	{-5, {51, -4, 0}, false}, // 1 {tag: -4}
	{-5, {41, -4, 0}, false}, // a {tag: -4}
	{-6, {41, 31, -5}, false}, // a == {tag: -5}
	{-6, {41, 32, -5}, false}, // a != {tag: -5}
	{-6, {41, 33, -5}, false}, // a > {tag: -5}
	{-6, {41, 34, -5}, false}, // a < {tag: -5}
	{-6, {41, 35, -5}, false}, // a >= {tag: -5}
	{-6, {41, 36, -5}, false}, // a <= {tag: -5}
	{-6, {51, 31, -5}, false}, // 1 == {tag: -5}
	{-6, {51, 32, -5}, false}, // 1 != {tag: -5}
	{-6, {51, 33, -5}, false}, // 1 > {tag: -5}
	{-6, {51, 34, -5}, false}, // 1 < {tag: -5}
	{-6, {51, 35, -5}, false}, // 1 >= {tag: -5}
	{-6, {51, 36, -5}, false}, // 1 <= {tag: -5}
	{-100, {66, -6, 0}, false}, // if {tag: -6}
	{-100, {-5, -4, 0}, false}, // {tage: -5} {tag: -4}
	{-100, {63, -2, 0}, false}, // let {tag: -2}
	{-100, {62, 41, 0}, false}, // input a
	{-100, {64, 41, 0}, false}, // print a
	{-100, {61, 0, 0}, false}, // rem
	{0, {51, -100, 0}, false}, // 1 {tag: -100}
	{0, {51, 67, 0}, false}, // 1 end
	{0, {10, 0, 0}, false}, // <ENTER>
	{0, {3, 0, 0}, false}, // EOF
};

std::list<std::tuple<std::string, bool>> Token::variables = {};

bool Token::end = false;

int Token::GetToken(std::string str) {
	int posi = 0;
	bool num = true;
	while (posi < str.length()) {
		if (std::isdigit(str[posi++])) continue;
		num = false;
		break;
	}

	if (num)
		return 51;

	auto t = tokens; // auto = var
	
	for (auto i = t.begin(); i != t.end();) {
		std::string s = std::get<0>(*i);
		if (s.length() != str.length())
			i = t.erase(i);
		else 
			++i;
	}

	if (t.empty())
		return 0;

	posi = 0;

	while (posi < str.length()) {
		for (auto i = t.begin(); i != t.end();) {
			std::string s = std::get<0>(*i);
			if (s[posi] != str[posi])
				i = t.erase(i);
			else
				++i;
		}

		if (t.empty())
			return 0;

		posi++;
	}

	return std::get<1>(t.front());
}

int Token::RegisterVariable(std::string str) {
	variables.push_back({ str, false });
	return variables.size() - 1;
}

int Token::CheckVariables(std::string str) {
	int posi = 0;

	for (auto i = variables.begin(); i != variables.end(); ++i) {
		std::string s = std::get<0>(*i);
		if (str == s) break;
		posi++;
	}

	return posi >= variables.size() ? -1 : posi;
}

bool Token::VariableInited(std::string str) {
	for (auto i = variables.begin(); i != variables.end(); ++i) {
		std::string s = std::get<0>(*i);
		if (str != s) continue;
		return std::get<1>(*i);
	}
	return false;
}

void Token::InitVariable(std::string str) {
	for (auto i = variables.begin(); i != variables.end(); ++i) {
		std::string s = std::get<0>(*i);
		if (str != s) continue;
		*i = { str, true };
		return;
	}
}

int Token::CheckTokens(int a, int b, int c) {
	for (auto i = merge.begin(); i != merge.end(); ++i) {
		auto tupla = std::get<1>(*i);
		int x = std::get<0>(tupla), y = std::get<1>(tupla), z = std::get<2>(tupla);

		if (x == a && y == b && z == c)
			return std::get<0>(*i);

		if (std::get<2>(*i)) {
			if (x == c && y == b && z == a)
				return std::get<0>(*i);
		}
	}
	return 100;
}