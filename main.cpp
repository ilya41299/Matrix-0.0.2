#include "stdafx.h"
#include <iostream>
#include <sstream>

using namespace std;

bool R_S_C(int &rows, int &columns) {
	char sim;
	string R_S_C;
	getline(cin, R_S_C);
	istringstream stream(R_S_C);
	if (!(stream >> rows && stream >> sim && sim == ',' && stream >> columns)) {
		return false;
	}
	return true;
}

bool vvod_mas(float **mas, int rows, int columns)
{
	string stroka;
	for (int i = 0; i < rows; ++i) {
		mas[i] = new float[columns];
		getline(cin, stroka);
		istringstream stream(stroka);
		for (int j = 0; j < columns; j++) {
			if (!(stream >> mas[i][j])) {
				return false;
			}
		}
	}
	return true;
}

void add(float ** mas1, float ** mas2, int rows, int columns) {
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << mas1[i][j] + mas2[i][j] << " ";
		}
		cout << endl;
	}
}

void sub(float ** mas1, float ** mas2, int rows, int columns) {
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << mas1[i][j] - mas2[i][j] << " ";
		}
		cout << endl;
	}
}

void mult(float ** mas1, float ** mas2, int rows, int columns) {
	cout << endl;
	for (int  i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			float res = 0;
			for (int k = 0; k < rows; k++)
				res += mas1[i][k] * mas2[k][j];
			cout << res << " ";
		}
		cout << endl;
	}
}

void Trans(float ** mas, int rows, int columns) {
	float ** T_mas = new float *[rows];
	for (int i = 0; i < columns; i++) {
		T_mas[i] = new float[rows];
		for (int j = 0; j < rows; j++) {
			T_mas[i][j] = mas[j][i];
		}
	}
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			cout << T_mas[i][j] << " ";
		}
		cout << endl;
	}
}

void revers_mas(float ** mas, float ** mas1, int rows) {
	float a, b, result;
	for (int i = 0; i < rows; i++) {
		mas[i] = new float[rows];
		for (int j = 0; j < rows; j++) {
			mas[i][j] = 0;
			mas[i][i] = 1;
		}
	}
	for (int i = 0; i < rows; i++) {
		a = mas1[i][i];
		for (int j = i + 1; j < rows; j++) {
			b = mas1[j][i];
			for (int k = 0; k < rows; k++) {
				mas1[j][k] = mas1[i][k] * b - mas1[j][k] * a;
				mas[j][k] = mas[i][k] * b - mas[j][k] * a;
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = rows - 1; j > -1; j--) {
			result = 0;
			for (int k = rows - 1; k > j; k--) {
				result += mas1[j][k] * mas[k][i];
				if (mas1[j][j] == 0) {
					for (i = 0; i < rows; i++) {
						delete[] mas[i];
						delete[]mas;
					}
				}
			}
			mas[j][i] = (mas[j][i] - result) / mas1[j][j];
		}
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			cout << mas[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int rows1, rows2, columns1, columns2;
	char op;
	R_S_C(rows1, columns1);
	float ** mas1 = new float *[rows1];
	if (!(vvod_mas(mas1, rows1, columns1))) {
		cout << "An error has occured while reading input data";
		return -1;
	}
	cin >> op;
	if (op == 'T') {			
		Trans(mas1, rows1, columns1);
	}
	else if (rows1 == columns1 && (op == '-' || op == '+' || op == '*')) {		
		cin.get();
		R_S_C(rows2, columns2);
		float ** mas2 = new float *[rows2];
		if (vvod_mas(mas2, rows2, columns2) && rows1 == rows2 && columns1 == columns2) {
			switch (op) {
			case '+': {
				add(mas1, mas2, rows1, columns1);
				break; 
			}
			case '-': {
				sub(mas1, mas2, rows1, columns1);
				break; 
			}
			case '*': {
				mult(mas1, mas2, rows1, columns1);
				break; 
			}
			default: cout << "An error has occured while reading input data";
			}
		}
	}
		else if (op == 'R' && rows1 == columns1) {
			float **mas = new float *[columns1];
			revers_mas(mas, mas1, rows1);
		}
		else cout << "An error has occured while reading input data";
}
