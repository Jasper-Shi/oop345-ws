//Notifications
#pragma once
#include "Message.h"
using namespace std;

const size_t MAX_NOTIFICATIONS = 10;
namespace w5 {
	class Notifications {
		Message message[MAX_NOTIFICATIONS];
		size_t count = 0;
	public:
		Notifications() : count(0) //- default constructor - empty
		{

		}
		Notifications(const Notifications& src) : count(0) //- copy constructor
		{
			*this = src;
		}
		Notifications& operator=(const Notifications& src) //-copy assignment operator
		{
			if (this != &src) {
				count = src.count;
				for (int i = 0; i < MAX_NOTIFICATIONS; i++) {
					message[i] = src.message[i];
				}
			}
			return *this;
		}
		Notifications(Notifications&& src) //- move constructor
		{
			*this = move(src);
		}
		Notifications&& operator=(Notifications&& src) //-move assignment operator
		{
			if (this != &src) {
				count = src.count;
				for (int i = 0; i < MAX_NOTIFICATIONS; i++) {
					message[i] = src.message[i];
				}
				for (int i = 0; i < MAX_NOTIFICATIONS; i++) {
					src.message[i].release();
				}
			}
			return move(*this);
		}
		~Notifications() //- destructor
		{

		}
		void operator+=(const Message& msg) //- adds msg to the set
		{
			if (count < MAX_NOTIFICATIONS) {
				message[count] = msg;
				count++;
			}
			else {
				cout << "Notifications are full" << endl;
			}
		}
		void display(std::ostream& os) const //- inserts the Message objects to the os output stream
		{
			for (int i = 0; i < count; i++) {
				message[i].display(os);
				os << endl;
			}
		}
	};
}