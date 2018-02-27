#include "CString.h"
#include "Str.h"
#include <iostream>
#include <string>

using namespace std;
namespace w1 {
	CString::CString()
	{
		str[0] = '\0';
	}
	CString::CString(const char *src)
	{
		if (src != nullptr) {
			int i = 0;
			while (src[i] != '\0') {
				str[i] = src[i];
				i++;
			}
			NumOfChar++;
		}
		else {
			str[0] = '\0';
		}
	}

	int CString::length() const
	{
		return strlen(str);
	}

	void CString::display(std::ostream & os)
	{
		if (str[0] != '\0') {
			os << str;
		}
	}

	const char* CString::returnChar()
	{
		return str;
	}
	
	std::ostream & operator<<(std::ostream & os, CString & s)
	{
		os << s.returnChar();

		return os;
	}

}

