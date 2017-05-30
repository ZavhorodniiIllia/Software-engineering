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

	/**********************************************************Lexical analyzer**********************************************************************************/

	while(!file.eof()) {
		switch (letter(ch)) {
		case 0: {
			file.get(ch);
			break;
		}
		case 1: {
			while (ch != ' ' && chek3(ch) == false && ch != '\n') {
				if (letter(ch) == 1 ) {
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
			result << setw(10) <<mapchek1(buf) << setw(10) << row << setw(10) << collumn << setw(10) << buf << endl;
			break;
		}
		case 2: {
			while (ch != ' ' && chek3(ch) == false && ch != '\n') {
				if (letter(ch) == 1 || letter(ch)== 2 ){
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

	/**********************************************************Syntactical analyzer**********************************************************************************/
	
	numb();
	program();
	
	system("pause");
}