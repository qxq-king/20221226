#include <bits\stdc++.h>
#include <fstream>
#include "matrix.h"


#define null	0
#define ERR		"\033[33m\033[41m\033[01mERR!\033[0m "
#define WARN	"\033[43m\033[01mWARNING!\033[0m "
#define SUC		"\033[32mSuccess!\033[0m "

using namespace std;

int readData(char* filename, float** A, float** b);
void displayData(float* A, float* b, int N);
bool solve(float* A, float* b, float* x, int N);
void saveResult(char* filename, float* x, int N);

int main(){
	char fileName[] = "F:\\Debug\\cpp\\Ab.txt";//自定义路径和文件名
	char resultFileName[] = ".\\result.txt";//自定义路径和文件名

	float* A = null, * b = null, * x = null;
	int N = readData(fileName, &A, &b);
	if (N < 1) {
		cout << ERR << "Wrong data." << endl;
		return 1;
	}


	displayData(A, b, N);


	x = new float[N];
	bool ok = solve(A, b, x, N);


	if (ok){
		cout << SUC << "Solution:" << endl;
		for (int i = 0; i < N; i++)
			cout << " x" << i + 1 << "\t= " << x[i] << endl;
	}
	else
		cout << WARN << "Solution Failure!\n";

	if (A != null){
		saveResult(resultFileName, x, N);
		delete[]A;
		delete[]b;
		delete[]x;
	}
	return 0;
}

int readData(char filename[], float** A, float** b) {
	int N;
	ifstream fin(filename);
	if (!fin) {
		cout << ERR << "Cannot open \"" << filename << "\". File Missing!" << endl;
		return 0;
	}
	cout << SUC << "Succefully open \"" << filename << "\"" << endl;
	fin >> N;
	*A = new float[N * N];
	*b = new float[N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> (*A)[i * N + j];
		}
		fin >> (*b)[i];
	}
	fin.close();
	return N;
}

void displayData(float* A, float* b, int N) {
	if (A == null)
		cout << ERR << "empty data." << endl;
	else {
		cout << "\033[32mOutput Matix \033[0m(A,b)：" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				A[i * N + j] >= 0 ? cout << " " << A[i * N + j] << "\t" : cout << A[i * N + j] << "\t";
			b[i] >= 0 ? cout << " " << b[i] << "\n" : cout << b[i] << "\n";
		}
	}
}

bool solve(float* A, float* b, float* x, int N){
	float** COE = new float* [N];
	for (int i = 0; i < N; i++) { COE[i] = new float[N + 1]; }
	for (int i = 0; i < N; i++) { for (int j = 0; j < N; j++) { COE[i][j] = A[i * N + j]; }COE[i][N] = b[i]; }
	int RA = arithmetic::anti_arr_matrix_rank(COE, N, N + 1), RB = arithmetic::anti_arr_matrix_rank(COE, N, N);
	if (RA == RB && RA == N) {
		for (int i = N - 1; i >= 0; i--) {
			float bc = COE[i][N];
			for (int j = N - 1; j > i; j--) { bc -= COE[i][j] * x[j]; }
			x[i] = bc / COE[i][i];
		}
		return true;
	}
	else
		return false;
}

void saveResult(char* filename, float* x, int N){
	ofstream fout(filename);
	if (fout.is_open()){
		for (int i = 0; i < N; i++) {
			fout << " x" << i + 1 << "\t= " << x[i] << endl;
		}
		fout.close();
		cout << SUC << "Successfully saved the result to \"" << filename << "\"" << endl;
		cout << SUC << "Successfully openned file at \"" << filename << "\"." << endl;
		system(filename);
	}
	else 
		cout << ERR << "Cannot write to file. File Unwritable." << endl;
	return;
}