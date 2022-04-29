#pragma once
#pragma once
#include "Elemento.h"
#include <vector>
#include "Diagrama.h"
#include "CConjunto.h"

using namespace std;
//using namespace System;


struct SubConjunto
{
	Elemento* elemento1;
	Elemento* elemento2;
	Elemento* elementomci;
	Elemento* elementomcs;
};

class CComprobar
{
public:
	CComprobar();
	CComprobar(CConjunto* objconjunto, bool** matriz, int N, Diagrama* objdiagrama)
	{
		this->matriz = matriz;
		this->objconjunto = objconjunto;
		this->objdiagrama = objdiagrama;
		this->N = N;
		reticula = false;
	}
	~CComprobar();

	bool Comprobar_Reticula();
	void Complemento_Reticula();

	void Hallar_MCI_MCS(SubConjunto* S, int i, int j);
	int Devuelve_Posicion(int n);
	bool mostrar(int j);
	bool tiene_complemento(int n);

private:
	int N;
	bool** matriz;
	bool reticula;
	vector<SubConjunto> subconjuntos;
	CConjunto* objconjunto;
	Diagrama* objdiagrama;

};

CComprobar::CComprobar() {}
CComprobar::~CComprobar() {}

bool CComprobar::Comprobar_Reticula()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (matriz[i][j] == 0 && matriz[j][i] == 0) {
				SubConjunto S;
				S.elemento1 = objdiagrama->getVector()[Devuelve_Posicion(i)];
				S.elemento2 = objdiagrama->getVector()[Devuelve_Posicion(j)];
				Hallar_MCI_MCS(&S, i, j);
				subconjuntos.push_back(S);
			}
		}
	}

	for (int i = 0; i < subconjuntos.size(); i++) {
		if (subconjuntos[i].elementomci == 0) {
			cout << "El subconjunto (" << subconjuntos[i].elemento1->getN() << "," << subconjuntos[i].elemento2->getN() << ") no tiene MCI" << endl;
			return false;
		}
		else {
			reticula = true;
			//if (mostrar(i)) {
			cout << "La MCI del subconjunto (" << subconjuntos[i].elemento1->getN() << "," << subconjuntos[i].elemento2->getN() << ") es " << subconjuntos[i].elementomci->getN() << "." << endl;
			//}
		}

		if (subconjuntos[i].elementomcs == 0) {
			cout << "El subconjunto (" << subconjuntos[i].elemento1->getN() << "," << subconjuntos[i].elemento2->getN() << ") no tiene MCS" << endl;
			return false;
		}
		else {
			reticula = true;
			//if (mostrar(i)) {
			cout << "La MCS del subconjunto (" << subconjuntos[i].elemento1->getN() << "," << subconjuntos[i].elemento2->getN() << ") es " << subconjuntos[i].elementomcs->getN() << "." << endl;
			//}
		}

	}
	return reticula;
}

void CComprobar::Hallar_MCI_MCS(SubConjunto* S, int i, int  j)
{
	vector<Elemento*> canmci; //candidatos mci
	vector<Elemento*> canmcs;//candidatos mcs

	for (int k = 0; k < N; k++)
	{
		if (matriz[k][i] == 1 && matriz[k][j] == 1)
		{
			if (objdiagrama->getVector()[Devuelve_Posicion(k)]->getCorrespondencia() > S->elemento1->getCorrespondencia()
				&& objdiagrama->getVector()[Devuelve_Posicion(k)]->getCorrespondencia() > S->elemento2->getCorrespondencia())
			{
				canmci.push_back(objdiagrama->getVector()[Devuelve_Posicion(k)]);
			}

		}

		if (matriz[i][k] == 1 && matriz[j][k] == 1) {
			if (objdiagrama->getVector()[Devuelve_Posicion(k)]->getCorrespondencia() < S->elemento1->getCorrespondencia()
				&& objdiagrama->getVector()[Devuelve_Posicion(k)]->getCorrespondencia() < S->elemento2->getCorrespondencia())
			{
				canmcs.push_back(objdiagrama->getVector()[Devuelve_Posicion(k)]);
			}
		}
	}

	if (canmci.size() == 1) { S->elementomci = canmci[0]; }
	if (canmci.empty()) {
		S->elementomci = 0;//verificar
	}
	if (canmci.size() > 1)
	{
		int mayor = -1;
		for (int m = 0; m < canmci.size(); m++) {
			if (canmci[m]->getCorrespondencia() > mayor) {
				mayor = canmci[m]->getCorrespondencia();
			}
		}

		int cont = 0;//cont =contador
		for (int m = 0; m < canmci.size(); m++) {
			if (canmci[m]->getCorrespondencia() == mayor)
			{
				cont++;
			}
		}

		if (cont > 1) {
			S->elementomci = 0; //verificar
		}

		if (cont == 1) {
			for (int m = 0; m < canmci.size(); m++) {
				if (canmci[m]->getCorrespondencia() == mayor) {
					S->elementomci = canmci[m];
				}
			}
		}
	}

	//MCS
	if (canmcs.size() == 1) { S->elementomcs = canmcs[0]; }
	if (canmcs.empty()) {
		S->elementomcs = 0;//verificar
	}
	if (canmcs.size() > 1)
	{
		int mayor = -1;
		for (int m = 0; m < canmcs.size(); m++) {
			if (canmcs[m]->getCorrespondencia() > mayor) {
				mayor = canmcs[m]->getCorrespondencia();
			}
		}

		int cont = 0;//cont =contador
		for (int m = 0; m < canmcs.size(); m++) {
			if (canmcs[m]->getCorrespondencia() == mayor) {
				cont++;
			}
		}

		if (cont > 1) {
			S->elementomcs = 0; //verificar
		}

		if (cont == 1) {
			for (int m = 0; m < canmcs.size(); m++) {
				if (canmcs[m]->getCorrespondencia() == mayor) {
					S->elementomcs = canmcs[m];
				}
			}

		}
	}
}

void CComprobar::Complemento_Reticula()
{
	cout << "Elemento \tComplemento" << endl;
	for (int i = 0; i < objconjunto->getN(); i++) {
		cout << objconjunto->getarreglo(i) << "\t\t";

		if (i == 0) {
			cout << objconjunto->getarreglo(objconjunto->getN() - 1) << endl;
		}
		else {
			if (i == objconjunto->getN() - 1) {
				cout << objconjunto->getarreglo(0) << endl;
			}
			else {

				if (!tiene_complemento(objconjunto->getarreglo(i))) {
					cout << "No tiene" << endl;
				}
			}
		}
	}
}

bool CComprobar::tiene_complemento(int n) {

	for (int j = 0; j < subconjuntos.size(); j++) {

		if (n == subconjuntos[j].elemento1->getN()) {

			if (subconjuntos[j].elementomci->getN() == objconjunto->getarreglo(0) &&
				subconjuntos[j].elementomcs->getN() == objconjunto->getarreglo(objconjunto->getN() - 1)) {

				cout << subconjuntos[j].elemento2->getN() << endl;
				return true;
			}
		}
	}
	return false;
}

int CComprobar::Devuelve_Posicion(int x)
{
	int n = objconjunto->getarreglo(x);
	for (int i = 0; i < N; i++)
	{
		if (n == objdiagrama->getVector()[i]->getN())
		{
			return i;
		}
	}
}

bool CComprobar::mostrar(int i) {
	bool muestra = false;
	for (int j = 0; j < i; j++) {
		if (subconjuntos[i].elemento1->getN() == subconjuntos[j].elemento2->getN() && subconjuntos[i].elemento2->getN() == subconjuntos[j].elemento1->getN()) {
			return false;
		}
		else {
			muestra = true;
		}
	}
	return muestra;
}

