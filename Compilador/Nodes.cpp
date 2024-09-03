#include <string>
#include "Nodes.h"

int value = 0;

void N0(std::string str, int count = 0) {
	if (str.length() <= count)
		return;
	value = 0;
}

void N1(std::string str, int count = 0) {
	if (str.length() <= count)
		return;

	switch (str[count]) {
	case 'i':
		if (!value)
			value = -1; // If | Input
		else if (value == -12)
			value = -13; // prInt
		N1(str, count + 1);
		break;
	case 'f':
		if (value == -1)
			value == 66; //iF
		N1(str, count + 1);
		break;
	case 'n':
		if (value == -1)
			value = -6; //iNput
		else if (value == -9)
			value = -10; // eNd
		else if (value == -13)
			value = -14; // priNt
		N1(str, count + 1);
		break;
	case 'p':
		if (value == -6)
			value = -7; // inPut
		else if (!value && !count)
			value = -11; // Print
		N1(str, count + 1);
		break;
	case 'u':
		if (value == -7) {
			value = -8; // inpUt
			N1(str, count + 1);
		}
	case 'r':
		if (!value)
			value = -2; //Rem
		else if (value == -11)
			value = -12; // pRint
		N1(str, count + 1);
		break;
	case 'l':
		if (!value)
			value = -4; //Let
		N1(str, count + 1);
		break;
	case 'e':
		if (!value)
			value = -9; // End
		else if (value == -2)
			value = -3; //rEm
		else if (value == -4)
			value = -5; //lEt
		N1(str, count + 1);
		break;
	case 'm':
		if (value == -3)
			value = 61; // reM
		N0(str, count + 1);
		break;
	case 't':
		if (value == -5)
			value = 63; // leT
		else if (value == -8)
			value = 62; // inpuT
		else if (value == -14)
			value = 64; // prinT
		else if (value == -16) {
			value = -17;
			N1(str, count + 1);
			break;
		}
		N0(str, count + 1);
		break;
	case 'd':
		if (value == -10)
			value = 67; // enD
		N0(str, count + 1);
		break;
	case 'g':
		if (!value)
			value = -15; // Goto
		N1(str, count + 1);
		break;
	case 'o':
		if (value == -15) {
			value = -16;
			N1(str, count + 1);
		} else if (value == -17) {
			value = 65;
			N0(str, count + 1);
		}
	}

	if (value <= 0 && count == 0) {
		value = 41;
		N0(str, count + 1);
	}
}