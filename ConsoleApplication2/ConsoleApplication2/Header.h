#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>


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

/*--------------------Lexical analyzer-------------------*/

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

/*--------------------Syntactical analyzer-------------------*/
string num[100];
int i_num;
bool flag = true;
int error;
ifstream syn("result.txt");
ofstream syn_result("result2.txt");

void numb() {
	char ch;
	string buf;
	syn.get(ch);
	int i=0;

	while (!syn.eof()) {
		while (ch == ' ') {
			syn.get(ch);
		}
		while (ch != ' ') {
			buf = buf + ch;
			syn.get(ch);
		}
		do {
			syn.get(ch);
		} while (ch != '\n');
		syn.get(ch);
		num[i] = buf;
		i++;
		buf.clear();
	}
}

string num_chek(int number) {
	string res;
	while (number < 100) {
		if (number == int(';')) {
			syn_result << '\t' << '\t' << '\t' << ';' << endl;
		}
		else if (number == int('.')) {
			syn_result << '\t' << '\t' << '\t' << '.' << endl;
		}
		else if (number == int('=')) {
			syn_result << '\t' << '\t' << '\t' << '=' << endl;
		}
		i_num++;
		number = atoi(num[i_num].c_str());
	}
	if (number > 400 && number < 500) {
		auto i = KeyWord.begin();
		for (i; i != KeyWord.end(); i++) {
			if (number == i->first) {
				res = KeyWord[i->first];
				break;
			}
		}
	}
	else if (number > 500 && number < 600) {
		auto i = Identifiers.begin();
		for (i; i != Identifiers.end(); i++) {
			if (number == i->first) {
				res = Identifiers[i->first];
				break;
			}
		}
	}
	else if (number > 600) {
		auto i = Constants.begin();
		for (i; i != Constants.end(); i++) {
			if (number == i->first) {
				res = Constants[i->first];
				break;
			}
		}
	}

	return res;
}


/*string sign() {
	int j;
	string word;
	j = atoi(num[i_num].c_str());
	i_num++;
	word = num_chek(j);
	bool f = false;
	auto i = Constants.begin();
	for (i = Constants.begin(); i != Constants.end(); i++) {
		if (word == Constants[i->first]) {
			f = true;
			break;
		}
	}
	if (f == true || word == "+") {
		syn_result << "<sign>" << endl << '\t' << '+' << endl;
	}
	else if (word == "-") {
		syn_result << "<sign>" << endl << '\t' << word << endl;
		j = atoi(num[i_num].c_str());
		i_num++;
		word = num_chek(j);
	}
	return word;
}

void cons() {
	int j;
	string word;
	bool f = false;
	auto i = Constants.begin();
	syn_result << "<constant>" << endl;
	word = sign();
	for (i = Constants.begin(); i != Constants.end(); i++) {
		if (word == Constants[i->first]) {
			f = true;
			break;
		}
	}
	if (f == true) {
		syn_result << '\t' << word << endl;
		cons();
	}
}*/


void ident() {
	int j;
	string word;
	j = atoi(num[i_num].c_str());
	i_num++;
	word = num_chek(j);
	auto i = Identifiers.begin();
	for (i; i != Identifiers.end(); i++) {
		if (word == Identifiers[i->first]) {
			syn_result << '\t' << '\t' << '\t' << "<identifier>" << endl << '\t' << '\t' << '\t' << '\t' << word << endl;
			break;
		}
		else {
			if (i == Identifiers.end()) {
				flag = false;
				error = 1;
			}
		}
	}

}

void cons_ident(string word) {
	auto i = Identifiers.begin();
	for (i; i != Identifiers.end(); i++) {
		if (word == Identifiers[i->first]) {
			syn_result << '\t' << '\t' << '\t' << '\t' << '\t' << "<constant-identifier>" << endl << '\t' << '\t'<< '\t' << '\t' << '\t' << '\t' << '\t' << word << endl;
			break;
		}
		else{
			if (i == Identifiers.end()) {
				flag = false;
				error = 3;
			}
		}
	}

}

void proc_ident() {
	int j;
	string word;
	j = atoi(num[i_num].c_str());
	word = num_chek(j);
	syn_result << '\t' <<  "<procedure-identifiers>" << endl;
	ident();
}


void cons() {
	int j;
	string word;
	auto i = Constants.begin();
	i_num++;
	j = atoi(num[i_num].c_str());
	word = num_chek(j);
	for (i = Constants.begin(); i != Constants.end(); i++) {
		if (word == Constants[i->first]) {
			syn_result << '\t' << '\t' << '\t' << '\t' << "<constant>" << endl << '\t' << '\t' << '\t' << '\t' << '\t' << word << endl;
			break;
		}
		else{
			if (i == Constants.end()) {
				flag = false;
				error = 2;
			}
		}
	}
}

void cons_decl() {
	int j;
	string word;
	auto i = Identifiers.begin();
	j = atoi(num[i_num].c_str());
	word = num_chek(j);

	for (i = Identifiers.begin(); i != Identifiers.end(); i++) {
		if (word == Identifiers[i->first]) {
			syn_result << '\t' << '\t' << '\t' << "<constant-declarations-list>" << endl << '\t' << '\t' << '\t' << '\t' << "<constant-declaration>" << endl;
			cons_ident(word);
			if (flag == true) {
				cons();
				if (flag == true) {
					i_num++;
					j = atoi(num[i_num].c_str());
					word = num_chek(j);
				}
			}
		}
	}
}

string cons_decls() {
	int j;
	string word;
	auto i = Identifiers.begin();
	j = atoi(num[i_num].c_str());
	i_num++;
	word = num_chek(j);
	if (word == "CONST") {
		syn_result << '\t' << '\t' << "<constant-declarations>" << endl << '\t' << '\t' << '\t' << word << endl;
		j = atoi(num[i_num].c_str());
		word = num_chek(j);
			for (i = Identifiers.begin(); i != Identifiers.end(); i++) {
				if (word == Identifiers[i->first]) {
					cons_decl();	
				}
			}
			j = atoi(num[i_num].c_str());
			word = num_chek(j);
		}

	else {
		flag = false;
		error = 4;
		}
	return word;
}

string decl() {
	string word;
	syn_result << '\t' << "<declarations>" << endl;
	word = cons_decls();
	return word;
}

void stat_list() {
	/*EMPTY*/
	syn_result << '\t' << '\t' << "<statements-list>" << endl;
}

void block() {
	int j;
	string word;
	j = atoi(num[i_num].c_str());
	word = num_chek(j);
	syn_result << "<block>" << endl;
	word = decl();
	if (flag == true) {
		if (word == "BEGIN") {
			syn_result << '\t' << word << endl;
			stat_list();
			i_num++;
			j = atoi(num[i_num].c_str());
			word = num_chek(j);
			if (word == "END") {
				syn_result << '\t' << word << endl << '\t' << '.' << endl;
			}
			else {
				flag = false;
				error = 6;
			}
		}
		else {
			flag = false;
			error = 5;
		}
	}
	
}

void program() {
	int j;
	string word;
	i_num = 0;
	j = atoi(num[i_num].c_str());
	i_num++;
	word = num_chek(j);
	if (word == "PROGRAM") {
		syn_result << "<program>" << endl << '\t' << word << endl;
		proc_ident();
		if (flag == true) {
			block();
		}
	}
	else{
		flag = false;
		error = 0;
	}
	if(flag == false){
		syn_result << "ERROR:";
		switch (error)
		{
		case 0: {
			syn_result << "inncorrect PROGRAM" << endl;
			break;
		}
		case 1: {
			syn_result << "inncorrect identyfier" << endl;
			break;
		}
		case 2: {
			syn_result << "inncorrect constant" << endl;
			break;
		}
		case 3: {
			syn_result << "inncorrect constant-identyfier" << endl;
			break;
		}
		case 4: {
			syn_result << "inncorrect CONST" << endl;
			break;
		}
		case 5: {
			syn_result << "inncorrect BEGIN" << endl;
			break;
		}
		case 6: {
			syn_result << "inncorrect END" << endl;
			break;
		}
		default:
			break;
		}
	}
}
