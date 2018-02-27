#include "process.h"


void process(char * string[])
{
	w1::CString String(*string);
	cout << String.returnChar() << endl;
}
