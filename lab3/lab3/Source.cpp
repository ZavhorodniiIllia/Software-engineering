#include "Header.h"


int main() {
	char ch;
	bool f = false;
	string buf;
	string line;
	ifstream file("task.txt");
	ofstream result("result.txt");
	file.get(ch);
	int row = 1;
	int collumn = 1;

	/*----------------------------------------------------------------Lexical analyzer-------------------------------------------------*/

	while (!file.eof()) {
		switch (letter(ch)) {
		case 0: {
					file.get(ch);
					break;
		}
		case 1: {
					while (ch != ' ' && chek3(ch) == false && ch != '\n') {
						if (letter(ch) == 1) {
							buf = buf + ch;
							file.get(ch);
							++collumn;
							if (ch == '\n')
								++row;
						}
						else if (letter(ch) == 9) {
							f = true;
							break;
						}
					}
					if (f == true)
						break;
					result << setw(10) << mapchek1(buf) << setw(10) << row << setw(10) << collumn << setw(10) << buf << endl;
					break;
		}
		case 2: {
					while (ch != ' ' && chek3(ch) == false && ch != '\n') {
						if (letter(ch) == 1 || letter(ch) == 2){
							buf = buf + ch;
							file.get(ch);
							++collumn;
							if (ch == '\n')
								++row;
						}
						else if (letter(ch) == 9) {
							f = true;
							break;
						}
					}
					if (f == true)
						break;
					result << setw(10) << mapchek2(buf) << setw(10) << row << setw(10) << collumn << setw(10) << buf << endl;
					break;
		}
		case 3: {
					result << setw(10) << int(ch) << setw(10) << row << setw(10) << collumn << setw(10) << ch << endl;
					file.get(ch);
					++collumn;
					if (ch == '\n')
						++row;
					break;
		}
		case 4: {
					file.get(ch);
					if (ch == '*') {
						do {
							do {
								file.get(ch);
							} while (ch != '*');
							file.get(ch);
						} while (ch != ')');
					}
					else
						f = true;
					file.get(ch);
					break;
		}
		default: {
					 f = true;
					 break;
		}
		}
		if (f == true) {
			cout << "Error" << endl;
			break;
		}
		buf.clear();
		if (ch == '\n')
			file.get(ch);;
	}
	file.close();
	result.close();

	/*--------------------------------------------------------Syntactical analyzer-------------------------------------------------------*/
	numb();
	program();

	/*---------------------------------------------------------Code generator---------------------------------------------------*/

	ifstream code("result2.txt");
	ofstream code_res("result3.txt");
	code.get(ch);
	string buf1 = "";
	buf = "";
	bool falg = false;

	while (!code.eof()) {
		if (ch == '\t') {
			while (ch == '\t') {
				code.get(ch);
			}
		}
		if (ch == '<') {
			buf1.clear();
			code.get(ch);
			while (ch != '>') {
				buf1 = buf1 + ch;
				code.get(ch);
			}
			code.get(ch);
		}
		switch (letter(ch)) {
		case 1: {
			while (ch != '\n') {
				buf = buf + ch;
				code.get(ch);
			}
			falg = true;
			break;
		}
		case 2: {
			while (ch != '\n') {
				buf = buf + ch;
				code.get(ch);
			}
			falg = true;
			break;
		}
		case 3: {
			code.get(ch);
		}
		default: {
			break;
		}
		}
		if (ch == '\n') {
			code.get(ch);
		}
		if (buf == "PROGRAM") {
			code_res << ';';
		}
		else if (buf == "CONST") {
		
		}
		else if (buf == "LABLE") {
			
		}
		else if (buf == "BEGIN") {
			code_res << "data ends" << endl;
			code_res << "code segment" << endl;
			code_res << "assume cs:code ds:dats" << endl;
			code_res << "org 100h" << endl;
			code_res << "begin:" << endl;
		}
		else if (buf == "END") {
			code_res << "code ends" << endl;
			code_res << "end begin" << endl;
		}
		else {
			if (falg == true) {
				if (buf1 == "identifier") {
					code_res << buf << ".asm" << endl;
					code_res << "data segment" << endl;
					buf1.clear();
				}
				else if (buf1 == "constant-identifier") {
					code_res << buf << "	dd	";
					buf1.clear();
				}
				else if (buf1 == "constant") {
					code_res << buf << endl;
					buf1.clear();
				}
				else if (buf1 == "lable") {
					code_res << buf;
					buf1.clear();
				}
			}
		}
		buf.clear();
		falg = false;
	}

	system("pause");
}