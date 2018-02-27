#include "process.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	cout << "Command Line : ";
	int i = 0;
	for (int n = 0; n < argc; n++) {
		//cout << i << ": ";
		process(&argv[n]);
		cout << argv[n] << " ";
		i++;
	}
	if (argc > 1) {
		cout << endl;
		cout << "Maximum number of characters stored : " << argc << endl;
		for (int a = 0; a < i - 1; a++) {
			
			cout << a << ": " << argv[a + 1] << endl;
		}
	}
	else if (argc == 1) {
		cout << endl;
		cout << "Insufficient number of arguments (min 1)" << endl;
	}
	if (argc < 1) {
		return 1;
	}
	else {
		return 0;
	}
}
