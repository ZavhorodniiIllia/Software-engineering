#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;


 map <int, string> KeyWord = { {401,"PROGRAM" },
							  {402,  "CONST" },
							  {403,  "BEGIN" },
							  {404,    "END" } };

map <int, string> Identifiers = { {500 ,"ident"} };

map <int, string> Constants = { {600,"0"} };

char alfabet[52] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
					'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'z',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
					'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', };

char number[13] = {'0','1','2','3','4','5','6','7','8','9','#', '+', '-' };

char sep[4] = { ';', ',', '=','.' };

/**********************************************************Lexical analyzer**********************************************************************************/

bool chek1(char ch) {
	bool f = false;
	for (int i = 0; i < 13; i++) {
		if (ch == number[i]) {
			f = true;
			break;
		}
	}
	return f;
}

bool chek2(char ch) {
	bool f = false;
	for (int i = 0; i < 52; i++) {
		if (ch == alfabet[i]) {
			f = true;
			break;
		}
	}
	return f;
}

bool chek3(char ch) {
	bool f = false;
	for (int i = 0; i < 4; i++) {
		if (ch == sep[i]) {
			f = true;
			break;
		}
	}
	return f;
}

int letter(char ch) {
	int ret;
	do {
		if (ch == ' ') {
			ret = 0;
			break;
		}
		else if (chek1(ch) == true) {
			ret = 1;
			break;
		}
		else if (chek2(ch) == true) {
			ret = 2;
			break;
		}
		else if (chek3(ch) == true) {
			ret = 3;
			break;
		}
		else if (ch == '(') {
			ret = 4;
			break;
		}
		else {
			ret = 9;
			break;
		}

	} while (1 == 1);
	return ret;
}

int mapchek1(string str) {
	int result;
	int a;
	bool f = false;
	auto i= Constants.begin();
	for (i; i != Constants.end(); i++) {
		if (str == Constants[i->first]) {
			f = true;
			result = i->first;
			break;
		}
	}
	auto j = Constants.rbegin();
	if (f==false) {
		a=j->first+1;
		Constants.insert(pair<int,string>(a,str));
		result = a;
	}

	return result;
}


int mapchek2(string str) {
	int result;
	int a;
	bool f = false;
	auto i = KeyWord.begin();
	for (i; i != KeyWord.end(); i++) {
		if (str == KeyWord[i->first]) {
			f = true;
			result = i->first;
			break;
			}
		}
	if (f == false) {
		for (i = Identifiers.begin(); i != Identifiers.end(); i++) {
			if (str == Identifiers[i->first]) {
				f = true;
				result = i->first;
				break;
			}
		}
		auto j = Identifiers.rbegin();
		if (f == false) {
			a=j->first+1;
			Identifiers.insert(pair<int, string>(a, str));
			result = a;
		}
	}
	return result;
}

/**********************************************************Syntactical analyzer**********************************************************************************/
