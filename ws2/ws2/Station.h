#pragma once
#include <string.h>
#include <string>
using namespace std;

enum PassType { Adult, Student };
namespace w2 {
	class Station {
		unsigned int Student;
		unsigned int Adult;
		string StaName;
	public:
		Station()
		{
			Student = 0;
			Adult = 0;
			StaName = "";
		}
		void set(const std::string& str, unsigned sp, unsigned ap)
		{
			StaName = str;
			Student = sp;
			Adult = ap;
		}
		void update(PassType type, int num)
		{
			if (type == 1)
				Student += num;
			else
				Adult += num;
		}
		unsigned inStock(PassType type) const
		{
			if (type == 1)
				return Student;
			else
				return Adult;
		}
		const std::string& getName() const
		{
			return StaName;
		}
	};
}