#include "Station.h"
#include <iostream>
#include<iomanip>
#include <fstream>
using namespace std;
namespace w2 {
	class Stations {
		int stNum;
		Station* station;
	public:
		Stations(char *str) {
			stNum = 0;
			ifstream f(str);
			int total = 0; int sn = 0, an = 0;	string name = ""; char temp[100];
			f >> total;		f.ignore();
			stNum = total;

			station = new Station[stNum];
			for (int i = 0; i < total; i++) {
				name = "";
				f.getline(temp, 99, ';');
				for (int j = 0; j < strlen(temp); j++)
					name += temp[j];
				f >> sn;		f.ignore();
				f >> an;
				//Station *st = new Station[total]; // can't declare as Station st[total]. value between [] should be const

				//st[i].set(name, sn, an);
				station[i].set(name, sn, an);
				//cout << station[i].getName() << " " << station[i].inStock(Student) << " " << station[i].inStock(Adult) << endl;
			}
		}

		void update() {
			cout << "Passes Sold :" << endl
				<< "-------------" << endl;
			for (int i = 0; i < stNum; i++) {
				int spSold = 0; int apSold = 0;
				cout << station[i].getName() << " " << endl;
				cout << " Student Passes sold : ";
				cin >> spSold;		spSold = spSold - (2 * spSold);
				cout << " Adult Passes sold : ";
				cin >> apSold;		apSold = apSold - (2 * apSold);
				station[i].update(Student, spSold);
				station[i].update(Adult, apSold);
			}
			cout << endl;
		}

		void restock() {
			cout << "Passes Added :" << endl
				<< "-------------" << endl;
			for (int i = 0; i < stNum; i++) {
				int spSold = 0; int apSold = 0;
				cout << station[i].getName() << " " << endl;
				cout << " Student Passes added : ";
				cin >> spSold;
				cout << " Adult Passes added : ";
				cin >> apSold;
				station[i].update(Student, spSold);
				station[i].update(Adult, apSold);
			}
			cout << endl;
		}

		void report() const {
			cout << "Passes in Stock : Student Adult" << endl;
			cout << "-------------------------------" << endl;
			for (int i = 0; i < 4; i++) {
				cout << left << setw(20) << station[i].getName();
				cout << setiosflags(ios::right) << setw(7) << station[i].inStock(Student) << "  ";
				cout << setiosflags(ios::right) << setw(2) << station[i].inStock(Adult) << endl;
			}
		}

		Stations() {

		}
	};
}