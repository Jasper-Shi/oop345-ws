#pragma once
#ifndef _I_PRODUCT_H_
#define _I_PRODUCT_H_

// Workshop 7 - STL Containers
// iProduct.h

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
static int index = 0;
namespace w7 {

	class iProduct {
	public:
		virtual double getCharge() const = 0;
		virtual void display(std::ostream&) const = 0;
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);

	iProduct* readProduct(std::ifstream& file) {
		size_t lineNum = 0;
		string temp = "", temp2 = "";
		Product *P;
		P->ProNumber = new string;
		P->price = new double;
		try {
			if (file.is_open()) {
				string line;
				while (getline(file, line))
					lineNum++;
				//
				file.clear();
				file.seekg(0);

				if (index < lineNum) {
					for (int i = 0; i < index; i++) {
						getline(file, temp);
						temp = "";
					}
					getline(file, temp, ' ');
					*P->ProNumber = temp;
					temp = "";

					getline(file, temp);
					for (int i = 0; i < temp.size(); i++) {
						if (temp[i] == ' ') {
							for (int j = 0; j < i; j++) {
								temp2 += temp[j];
							}
						}
					}
					if (temp2 == "")
						*P->price = stof(temp);
					else
						*P->price = stof(temp2);

					index++;
				}
				return P;
			}
		}
		catch (char* err) {
			cerr << err << endl;
			exit(0);
		}
	}


	class Product : public iProduct {
	public:
		string *ProNumber;
		double *price;

		double getCharge() const {
			return *price;
		}
		
		void display(std::ostream& os) const {
			os << "Product No      Cost Taxable" << endl;
		}
	
	};

}
#endif