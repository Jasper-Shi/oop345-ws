//Messages.h
#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;
namespace w5 {
	

	class Message {
		string name;
		string reply;
		string tweet;
	public:
		int countSpace(string str) {
			int num = 0;
			for (int i = 0; i < str.size(); i++) {
				if (str[i] == ' ')
					num++;
			}
			return num;
		}
		Message() {
			name = "";
			reply = "";
			tweet = "";
		}
		Message(std::ifstream& in, char c) //- constructor retrieves a record from the in file object, parses the record(as described above) and stores its components in the Message object.c is the character that delimits each record
		{
			string line;
			size_t index = 0;
			getline(in, line, c);
			
			if (countSpace(line) > 1) {
				while (index < line.size() && line[index] != ' ') {
					name += line[index];
					index++;
				}

				index++;//skip a space

				if (index < line.size() && line[index] == '@') {
					while (index < line.size() && line[index] != ' ') {

						reply += line[index];
						index++;
					}
					index++;//skip a space
				}
				else {
					reply = "nothing";
				}

				while (index < line.size()) {
					tweet += line[index];
					index++;
				}

			}
		}
		bool empty() const //- returns true if the object is in a safe empty state
		{
			if (reply == "" && name == "" && tweet == "") {
				return true;
			}
			else {
				return false;
			}
		}
		void display(std::ostream& os) const //- displays the Message objects within the container
		{
			os << "Message" << endl;
			if (reply == "nothing") {
				os << " User : " << name << endl;
				os << " Tweet : " << tweet << endl;
			}
			else {
				os << " User : " << name << endl;
				os << " Reply : " << reply << endl;
				os << " Tweet : " << tweet << endl;
			}

		}
		void release() {
			name.clear();
			reply.clear();
			tweet.clear();
		}
	};

	
}