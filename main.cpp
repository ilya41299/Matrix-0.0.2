#include "stdafx.h"
#include <iostream>
#include <sstream>

using namespace std;

void print_matrix(float **result_mas, unsigned int rows1, unsigned int columns1);

bool read_size(unsigned int &rows, unsigned int &columns) {
	char symbol;
	string string;
	getline(cin, string);
	istringstream stream(string);
	if (!(stream >> rows && stream >> symbol && symbol == ',' && stream >> columns)) {
		return false;
	}
	return true;
}
void create(unsigned int rows, unsigned int columns, float ** &elements)
{
	for (unsigned int i = 0; i < rows; i++) {
		elements[i] = new float[columns];
		for (unsigned int j = 0; j < columns; ++j) {
			elements[i][j] = 0.0f;
		}
	}
}


bool vvod_mas(float ** mas, unsigned int rows, unsigned int columns)
{
	string stroka;
	for (unsigned int i = 0; i < rows; ++i) {
		mas[i] = new float[columns];
		getline(cin, stroka);
		istringstream stream(stroka);
		for (unsigned int j = 0; j < columns; j++) {
			if (!(stream >> mas[i][j])) {
				return false;
			}
		}
	}
	return true;
}

void destroy(unsigned int rows, float ** &mas )
{
	for (unsigned int i = 0; i<rows; ++i) {
		delete[]mas[i];
	}
	delete[] mas;
	
}

void add(float ** mas1, float ** mas2, unsigned int rows, unsigned int columns, float ** &result_mas) {
	result_mas = new float *[rows];
	for (unsigned int i = 0; i < rows; i++) {
		result_mas[i] = new float[columns];
		for (unsigned int j = 0; j < columns; j++) {
			result_mas[i][j] = mas1[i][j] + mas2[i][j];
		}
	}
}

void sub(float ** mas1, float ** mas2, unsigned int rows, unsigned int columns, float ** &result_mas) {
	result_mas = new float *[rows];
	for (unsigned int i = 0; i < rows; i++) {
		result_mas[i] = new float[columns];
		for (unsigned int j = 0; j < columns; j++) {
			result_mas[i][j] = mas1[i][j] - mas2[i][j];
		}
	}
}

void mult(float ** mas1, float ** mas2, unsigned int rows1, unsigned int columns1, unsigned int rows2, unsigned int columns2, float ** &result_mas) {
	unsigned int result_rows = rows1;
	unsigned int result_columns = columns2;
	result_mas = new float *[result_rows];
	for (unsigned int i = 0; i<result_rows; ++i) {
		result_mas[i] = new float[result_columns];
		for (unsigned int j = 0; j<result_columns; ++j) {
			float result = 0.0f;
			for (unsigned int k = 0; k < columns1; ++k) {
				result += mas1[i][k] * mas2[k][j];
			}
			result_mas[i][j] = result;
		}
	}
}

void Trans(float ** &result_mas, float ** mas1, unsigned int rows, unsigned int columns) {
	result_mas = new float *[columns];
	for (unsigned int i = 0; i < columns; i++) {
		result_mas[i] = new float[rows];
		for (unsigned int j = 0; j < rows; j++) {
			result_mas[i][j] = mas1[j][i];
		}
	}
}

bool revers_mas(float ** &result_mas, float ** mas1, unsigned int rows) {
	float a, b, result;
	for (unsigned int i = 0; i < rows; i++) {
		result_mas[i] = new float[rows];
		for (unsigned int j = 0; j < rows; j++) {
			if (i == j) {
				result_mas[i][j] = 1.0f;
			}
			else result_mas[i][j] = 0.0f;
		}
	}
	for (unsigned int i = 0; i < rows; i++) {
		a = mas1[i][i];
		for (unsigned int j = i + 1; j < rows; j++) {
			b = mas1[j][i];
			for (unsigned int k = 0; k < rows; k++) {
				mas1[j][k] = mas1[i][k] * b - mas1[j][k] * a;
				result_mas[j][k] = result_mas[i][k] * b - result_mas[j][k] * a;
			}
		}
	}
	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = rows - 1; j >= 0; j--) {
			result = 0.0f;
			for (unsigned int k = rows - 1; k > j; k--) {
				result += mas1[j][k] * result_mas[k][i];
			}
			if (mas1[j][j] == 0.0f) {
				cout << "There is no reverse matrix" << endl;
				return false;
			}
			result_mas[j][i] = (result_mas[j][i] - result) / mas1[j][j];
		}
	}
	return true;
}

int main() {
	unsigned int rows1, rows2, columns1, columns2;
	char op;
	if (!(read_size(rows1, columns1))) {
		cout << "An error has occured while reading input data";
		return -1;
	}
	float ** mas1 = new float *[rows1];
	create(rows1, columns1, mas1);
	float ** result_mas;
	if (!(vvod_mas(mas1, rows1, columns1))) {
		cout << "An error has occured while reading input data";

		return -1;
	}
	cin >> op;
	if (op == '*') {
		cin.get();
		read_size(rows2, columns2);
		float ** mas2 = new float *[rows2];
		create(rows2, columns2, mas2);
		if (vvod_mas(mas2, rows2, columns2) && rows1 == columns2) {
			mult(mas1, mas2, rows1, columns1, rows2, columns2, result_mas);
			destroy(rows2, mas2);
			
		}
		else {
			cout << "An error has occured while reading input data" << endl;
			destroy( rows2,mas2);
			return -1;
		}
	}
	else if (op == 'T') {
		Trans(result_mas, mas1, rows1, columns1);
		print_matrix(result_mas, columns1, rows1);
		destroy(columns1, result_mas);


	}
	else if (op == 'R' && rows1 == columns1) {

		if (!(revers_mas(result_mas, mas1, rows1))) {
			return -1;
		}
		else
		{
			print_matrix(result_mas, rows1, columns1);
			destroy(rows1, result_mas);
		}
	}
	else if (op == '-' || op == '+') {
		cin.get();
		read_size(rows2, columns2);
		float ** mas2 = new float *[rows2];
		create(rows2, columns2, mas2);
		if (vvod_mas(mas2, rows2, columns2) && rows1 == rows2 && columns1 == columns2) {
			switch (op) {
			case '+': {
				add(mas1, mas2, rows1, columns1, result_mas);
				print_matrix(result_mas, rows1, columns1);
				destroy(rows1, result_mas);
				break;
			}
			case '-': {
				sub(mas1, mas2, rows1, columns1, result_mas);
				print_matrix(result_mas, rows1, columns1);
				destroy(rows1, result_mas);

				break;
			}
			default: cout << "An error has occured while reading input data";
			}
		}
		destroy(rows2, mas2);
		
	}
	else if (op != 'T' && op != 'R' && op != '+' && op != '-' && op != '*') {
		cout << "An error has occured while reading input data";
		destroy(rows1, mas1);
		destroy(rows1, result_mas);
		return -1;
	}
	
	destroy(rows1, mas1);

	return 0;
}

void print_matrix(float **result_mas, unsigned int rows1, unsigned int columns1) {
	cout << endl;
	for (unsigned int i = 0; i < rows1; i++) {
		for (unsigned int j = 0; j < columns1; j++) {
			cout << result_mas[i][j] << ' ';
		}
		cout << endl;
	}
}
