#ifndef W1_CSTRING_H
#define W1_CSTRING_H
#include <iostream>
namespace w1 {
	class CString {
		int NumOfChar = 0;
		char str[100];
	public:
		CString();
		CString(const char*);
		int length()  const;
		void display(std::ostream& os);
		const char* returnChar();
	};
	std::ostream& operator<<(std::ostream& os, CString& s);
}

#endif