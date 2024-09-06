#pragma once
#ifndef _TOKEN_
#define _TOKEN_

#include <tuple>
#include <list>
#include <string>

class Token {
private:
	static std::list<std::tuple<std::string, int>> tokens;
	static std::list<std::tuple<int, std::tuple<int, int, int>, bool>> unions;
	static std::list<std::tuple<std::string, bool>> variables;
	static std::list<std::tuple<int, char, int>> precedencia;
public:
	int GetToken(std::string);
	int RegisterVariable(std::string);
	int CheckVariables(std::string);
	bool VariableInited(std::string);
	void InitVariable(std::string);
};

#endif // !_TOKENS_