#pragma once
#ifndef _TOKEN_
#define _TOKEN_

#include <tuple>
#include <list>
#include <string>

class Token {
private:
	static std::list<std::tuple<std::string, int>> tokens;
	static std::list<std::tuple<int, std::tuple<int, int, int>, bool>> merge;
	static std::list<std::tuple<std::string, bool>> variables;

public:
	static bool end;
	static int GetToken(std::string);
	static int RegisterVariable(std::string);
	static int CheckVariables(std::string);
	static bool VariableInited(std::string);
	static void InitVariable(std::string);
	static int CheckTokens(int a, int b = 0, int c = 0);
};

#endif // !_TOKENS_