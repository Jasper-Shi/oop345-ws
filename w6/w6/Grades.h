#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Grades {
	string* stdId;
	double* grade;
	int count;
public:
	Grades() :stdId(nullptr), grade(nullptr), count(0)
	{

	}
	
	Grades(char* filename) {
		try {
			ifstream f(filename);
			if (f.is_open()) {
				string line;
				int num = 0;
				while (getline(f, line)) {
					num++;
				}
				count = num;
				f.clear();
				f.seekg(0);
				
				stdId = new string[count];
				grade = new double[count];

				string temp="";
				for (size_t i = 0; i < count; i++) {
					getline(f, temp, ' ');
					stdId[i] = temp;
					temp = "";
					getline(f, temp);
					grade[i] = stof(temp);
					temp = "";
				}
				f.close();
			}
			else {
				throw "Can not open the file.";
			}
		}
		catch (char* err) {
			cerr << err << endl;
			exit(0);
		}
	}

	template<typename T>
	void displayGrades(std::ostream& os, T letter) const {
		for (size_t i = 0; i < count; i++)
			os << stdId[i] << " " << grade[i] << "0 " << letter(grade[i]) << endl;
	}

	~Grades() {
		delete[] stdId;
		delete[] grade;
	}

	Grades(Grades&) = delete;
	Grades& operator=(Grades&) = delete;
	Grades(Grades&&) = delete;
	Grades&& operator=(Grades&&) = delete;
};