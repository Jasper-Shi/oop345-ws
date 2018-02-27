#pragma once
#include<iostream>
#include <fstream>
#include<string>
using namespace std;
namespace w3 {
	class Text {
		size_t s = 0; //C++14
		string *b = nullptr;
	public:
		Text() {

		}

		~Text() {
			delete[] b;
			b = nullptr;
		}

		Text(char* filename) {
			ifstream fin(filename, std::ios::in);
			//fin.open(filename);
			if (fin.is_open()) {
				string line;
				while (getline(fin, line))
					s++;
				//cout << "S: " << s << endl;

				b = new string[s];

				fin.clear(); 
				fin.seekg(0);

				for (int i = 0; i < s; i++) {
					getline(fin, b[i], '\n');
					//cout << b[i] << endl;
				}

				fin.close();
			}
			else {
				cerr << "Could not open the file " << filename << endl;
			}
		}

		Text(const Text& src) {
			*this = src;
		}

		Text& operator=(const Text& src) {
			if (this != &src) {
				delete[] b;
				b = nullptr;
				s = 0;

				s = src.s;
				b = new string[s];
				for (int i = 0; i < s; i++) {
					b[i] = src.b[i];
				}
			}
			else {
				cout << "Can't self copy" << endl;
			}
			return *this;
		}

		Text(const Text&& src) {
			*this = move(src);
		}

		Text& operator=(Text&& src) {
			if (this != &src) {
				delete[] b;

				b = src.b;
				s = src.s;

				src.b = nullptr;
				src.s = 0;
			}
			else {
				cout << "Can't self move" << endl;
			}
			return move(*this);
		}

		size_t size() const {
			return s;
		}

	};

}