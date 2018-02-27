// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}


	Grades grades(argv[1]);
	// define the lambda expression for letter
	auto letter = [](double grade)->std::string {
		string letterGrade;
		if (grade >= 90 && grade <= 100)
			letterGrade = "A+";
		else if (grade >= 80 && grade <= 89)
			letterGrade = 'A';
		else if (grade >= 75 && grade <= 79)
			letterGrade = "B+";
		else if (grade >= 70 && grade <= 74)
			letterGrade = 'B';
		else if (grade >= 65 && grade <= 69)
			letterGrade = "C+";
		else if (grade >= 60 && grade <= 64)
			letterGrade = 'C';
		else if (grade >= 55 && grade <= 59)
			letterGrade = "D+";
		else if (grade >= 50 && grade <= 54)
			letterGrade = 'D';
		else
			letterGrade = 'F';
		return letterGrade;
	};




	grades.displayGrades(std::cout, letter);




	std::cout << "Press any key to continue ... ";
	std::cin.get();
}