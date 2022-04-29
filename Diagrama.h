#pragma once
#include "Elemento.h"
#include "CConjunto.h"
#include "Validaciones.h"

class Diagrama {
	vector<Elemento*> elementos;
	Validaciones* OP;

public:
	Diagrama(CConjunto* conjunto, Validaciones* OP) {

		for (int i = 0; i < conjunto->getN(); i++) {
			Elemento* e = new Elemento(conjunto->getVector()[i]);
			elementos.push_back(e);
		}
		this->OP = OP;

		for (int i = 0; i < elementos.size(); i++) { correspondencia(i); }

		ordenar_vector();
		elementos[conjunto->getN() - 1]->setPunto(150, 5);

		for (int i = 1; i < conjunto->getN() - 1; i++) {
			do {
				elementos[i]->setPunto(elementos[i]->getPunto().X, rand() % (220 - 10 + 1) + 10);
			} while (elementos[i - 1]->getPunto().Y > elementos[i]->getPunto().Y);
		}
		reposicionar();
		elementos[0]->setPunto(150, 230);
	}
	~Diagrama() {}

	void dibujarDiagrama(Graphics^ g) {
		dibujarElementos(g);

		SolidBrush^ b = gcnew SolidBrush(Color::Red);
		Pen^ p = gcnew Pen(b, 3);

		for (int i = 0; i < elementos.size(); i++) {
			for (int j = 0; j < elementos.size(); j++) {
				if (OP->getMatrizR2()[i][j] == 2) {
					g->DrawLine(p, elementos[i]->getPunto(), elementos[j]->getPunto());
					g->FillEllipse(b, elementos[i]->getPunto().X - 5, elementos[i]->getPunto().Y - 5, 10, 10);
					g->FillEllipse(b, elementos[j]->getPunto().X - 5, elementos[j]->getPunto().Y - 5, 10, 10);
				}
			}
		}
	}

	void dibujarElementos(Graphics^ g) {
		for (int i = 0; i < elementos.size(); i++) { elementos[i]->dibujar(g); }
	}

	void reposicionar() {
		for (int i = 0; i < elementos.size(); i++) {
			for (int j = i + 1; j < elementos.size(); j++) {
				if (elementos[i]->getCorrespondencia() == elementos[j]->getCorrespondencia()) {
					elementos[j]->setPunto(0, elementos[i]->getPunto().Y);
				}
			}
		}
		asignarX();
		asignarY();
	}

	void asignarX() {
		int c = 1;

		for (int i = 0; i < elementos.size(); i++) {
			int correspondencia = elementos[i]->getCorrespondencia();
			int cont = contando(correspondencia);

			if (c <= cont) {
				int x = ((300 / (cont + 1)) * c);
				elementos[i]->setPunto(x, elementos[i]->getPunto().Y);
				c++;
			}
			if (c > cont) {
				c = 1;
			}
		}
	}

	void asignarY() {
		vector<int> correspondencias;
		for (int i = 0; i < elementos.size(); i++) {
			if (!existe(elementos[i]->getCorrespondencia(), correspondencias)) {
				correspondencias.push_back(elementos[i]->getCorrespondencia());
			}
		}
		int separacion;
		separacion = 220 / (correspondencias.size() - 1);
		int cont = 1;

		for (int i = 0; i < elementos.size(); i++) {
			if (i == 0) {
				elementos[i]->setPunto(elementos[i]->getPunto().X, 230);
			}
			else {
				if (i == elementos.size() - 1) {
					elementos[i]->setPunto(elementos[i]->getPunto().X, 10);
				}
				else {
					int y = 10 + (separacion * cont);
					elementos[i]->setPunto(elementos[i]->getPunto().X, y);
					if (correspondencias[cont] != elementos[i]->getCorrespondencia()) {
						cont++;
					}
				}
			}

		}
	}

	void ordenar_vector() {
		Elemento* aux;
		for (int i = 0; i < elementos.size(); i++) {
			for (int j = i + 1; j < elementos.size(); j++) {
				if (elementos[i]->getCorrespondencia() < elementos[j]->getCorrespondencia()) {
					aux = elementos[i];
					elementos[i] = elementos[j];
					elementos[j] = aux;
				}
			}
		}
	}

	vector<Elemento*> getVector() { return elementos; }

	bool existe(int n, vector<int> vec) {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] == n) {
				return true;
			}
		}
		return false;
	}

	int contando(int n) {
		int cont = 0;

		for (int i = 0; i < elementos.size(); i++) {
			if (elementos[i]->getCorrespondencia() == n) {
				cont++;
			}
		}
		return cont;
	}

	void correspondencia(int i) {
		int suma = 0;
		for (int j = 0; j < elementos.size(); j++) {
			suma += OP->getMatrizRelacion()[i][j];
		}

		elementos[i]->setCorrespondencia(suma);
	}

};
