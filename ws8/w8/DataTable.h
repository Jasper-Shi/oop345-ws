//Author: Ziyi Shi

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdio>
#include <iomanip>

using namespace std;

namespace w8 {

	template <typename T>
	class DataTable {
		std::vector<T> x;
		std::vector<T> y;
		size_t size_ = 0;
	public:
		DataTable(std::ifstream& fin, int fw, int dw) {
			string line = "";
			int numOfLines = 0;
			while (getline(fin, line))
				numOfLines++;
			size_ = numOfLines;

			fin.clear();
			fin.seekg(0);

			T X, Y;
			for (int i = 0; i < numOfLines; i++) {
				fin >> X;
				fin >> Y;
				x.push_back(X);
				y.push_back(Y);
			}

		}

		T mean() const // -returns the mean value of the dependent coordinate
		{
			T sum = 0.0;
			for (int i = 0; i < y.size(); i++) {
				sum += y[i];
			}

			return sum / y.size();
		}

		T sigma() const // -returns the standard deviation of the dependent coordinates
		{
			T ssd = 0.00;
			T a = 0.00;
			for (int i = 0; i < y.size(); i++) {
				a = a + pow((y[i] - mean()), 2);
			}
			ssd = pow(a / (y.size() - 1), 0.5);
			return ssd;
		}

		T median() const // -returns the median value of the dependent coordinate
		{
			std::vector<T> temp;
			for (int i = 0; i < y.size(); i++)
				temp.push_back(y[i]);
			std::sort(temp.begin(), temp.end());
			T median = temp.size() % 2 ? temp[temp.size() / 2] : (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2;

			return median;
		}

		void regression(T& slope, T& y_intercept) const // -returns the slope and intercept for the data set
		{
			T A, B, C, D, a1 = 0.00, sumx = 0.00, sumy = 0.00, a2 = 0.00;
			T E, F;
			for (int i = 0; i < size_; i++) {
				a1 = a1 + x[i] * y[i];
			}
			A = size_ * a1;
			for (int i = 0; i < size_; i++)
				sumx = sumx + x[i];
			for (int i = 0; i < size_; i++)
				sumy = sumy + y[i];
			B = sumx * sumy;
			for (int i = 0; i < size_; i++)
				a2 = a2 + pow(x[i], 2);
			C = size_ * a2;
			D = pow(sumx, 2);
			
			slope = (A - B) / (C - D);
			y_intercept = (sumy - slope * sumx) / size_;
		}

		void display(std::ostream& os) const // -displays the data pairs as shown below
		{
			os << "      x      y" << endl;
			for (int i = 0; i < size_; i++) {
				os << fixed << setprecision(2);
				os << right << setw(7) << x[i];
				os << right << setw(7) << y[i] << endl;
			}

		}
	};

	std::ostream& operator<<(std::ostream& os, const DataTable<float> &data)
	{
		data.display(os);
		return os;
	}

}