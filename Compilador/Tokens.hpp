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
	static std::list<std::string> variables;
	//static std::list<std::tuple<int, int[]>> precedencia;
public:
	int GetToken(std::string);
};

#endif // !_TOKENS_