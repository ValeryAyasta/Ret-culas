#pragma once
#include "CConjunto.h"
using namespace System;

class Validaciones {
	CConjunto* conjunto;
	bool** matriz_relacion;
	int** matriz_relacion2;

public:
	Validaciones(CConjunto* conjunto, bool** matriz) {
		this->conjunto = conjunto;
		matriz_relacion = matriz;
		matriz_relacion2 = hallarMR2();
	}
	Validaciones() {}
	Validaciones(CConjunto* conjunto) {
		this->conjunto = conjunto;
		matriz_relacion = generar_matriz();
		matriz_relacion2 = hallarMR2();
	}
	bool** generar_matriz() {
		int n = conjunto->getN();
		bool** matriz = new bool* [n];
		for (int i = 0; i < n; i++) {
			matriz[i] = new bool[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matriz[i][j] = rand() % 2;
			}
		}
		return matriz;
	}
	void mostrar_matriz() {
		cout << "\nMR: " << endl;
		int n = conjunto->getN();
		cout << "   ";
		for (int i = 0; i < n; i++) {
			cout << conjunto->getVector()[i] << " ";
		}cout << endl;

		for (int i = 0; i < n; i++) {
			int espacio = 0;
			cout << conjunto->getVector()[i] << " ";
			for (int j = 0; j < n; j++) {
				Console::ForegroundColor = ConsoleColor::Blue;
				Console::SetCursorPosition(3 + espacio, 7 + i);
				cout << matriz_relacion[i][j] << " ";
				espacio = espacio + 2;
				Console::ForegroundColor = ConsoleColor::White;
			}cout << endl;
		}cout << endl;
	}
	CConjunto* getConjunto() { return conjunto; }
	bool** getMatrizRelacion() { return matriz_relacion; }

	bool EsReflexiva() {
		bool reflexiva = false;
		for (int i = 0; i < conjunto->getN(); i++) {
			if (matriz_relacion[i][i]) {
				reflexiva = true;
			}
			else { return false; }
		}return reflexiva;
	}
	bool EsTransitiva() {
		bool transitiva = false;
		cout << "\nHallamos la MR^2:" << endl;
		for (int i = 0; i < conjunto->getN(); i++) {
			cout << "    ";
			for (int j = 0; j < conjunto->getN(); j++) {
				if (matriz_relacion2[i][j] > 0) {
					cout << "1 ";
				}
				else { cout << matriz_relacion2[i][j] << " "; }
			}cout << endl;
		}
		for (int i = 0; i < conjunto->getN(); i++) {
			for (int j = 0; j < conjunto->getN(); j++) {
				if (matriz_relacion2[i][j] >= 1 && matriz_relacion[i][j] == 1) {
					transitiva = true;
				}
				if (matriz_relacion[i][j] >= 1 && matriz_relacion2[i][j] == 0) {
					return false;
				}
			}
		}		return transitiva;
	}
	int** hallarMR2() {
		int n = conjunto->getN();
		int** matriz = new int* [n];
		for (int i = 0; i < n; i++) {
			matriz[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) { matriz[i][j] = hallar_termino(i, j); }
		}return matriz;
	}

	int hallar_termino(int i, int j) {
		int termino = 0;
		for (int k = 0; k < conjunto->getN(); k++) {
			termino += matriz_relacion[i][k] * matriz_relacion[k][j];
		}return termino;
	}
	int** getMatrizR2() { return matriz_relacion2; }

	bool EsAntisimetrica() {
		bool antisimetrica = false;
		int n = conjunto->getN();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matriz_relacion[i][j] == 1) {
					if (matriz_relacion[j][i] == 1) {
						if (i == j) {
							antisimetrica = true;
						}
						else { return false; }
					}
				}
			}
		}return antisimetrica;
	}

	bool EsOrdenParcial() {
		bool reflexiva, transitiva, antisimetrica;

		if (EsReflexiva()) { cout << "1) Es reflexiva" << endl;    reflexiva = true; }
		else { cout << "1) NO es reflexiva" << endl; reflexiva = false; }

		if (EsTransitiva()) { cout << "2) Es transitiva" << endl; transitiva = true; }
		else { cout << "2) NO es transitiva" << endl; transitiva = false; }

		if (EsAntisimetrica()) { cout << "3) Es antisimetrica" << endl; antisimetrica = true; }
		else { cout << "3) NO es antisimetrica" << endl; antisimetrica = false; }

		bool orden_parcial;
		if (reflexiva && antisimetrica && transitiva) { orden_parcial = true; }
		else { orden_parcial = false; }

		return orden_parcial;
	}
};