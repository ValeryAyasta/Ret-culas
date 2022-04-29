#pragma once
#include <iostream>
#include<vector>
using namespace std;


class CConjunto{
public:
	CConjunto();
	~CConjunto();
	CConjunto(int n);
	void agregarelemento(int k);
	void mostrar();
	int getN();
	vector<int> getVector();
	int getarreglo(int pos);
private:
	int n;
	vector<int>arreglo;
};

CConjunto::CConjunto(int n){this->n = n;}

CConjunto::CConjunto(){}
CConjunto::~CConjunto(){}

void CConjunto::agregarelemento(int k) {arreglo.push_back(k);}

void CConjunto::mostrar() {
	cout << "v = { ";
	for (int n : arreglo) {
		cout << n << ", ";
	}
	cout << "}; \n";
}
int CConjunto::getN() { return n; }
vector<int> CConjunto::getVector() { return arreglo; }
int CConjunto::getarreglo(int pos) {return arreglo[pos];}
