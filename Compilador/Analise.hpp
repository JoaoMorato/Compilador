#ifndef _ANALISE_
#define _ANALISE_
#pragma once

#include <string>

bool AnaliseLexica(int line, std::string linha);
bool AnaliseSintatica(int line, std::string linha);
int AnaliseSemantica(int line, int oldLine, std::string linha);

#endif // _ANALISE_