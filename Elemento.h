#pragma once
#include <iostream>
using namespace System::Drawing;

class Elemento {
	Point punto;
	int ancho, alto;
	int n;
	int correspondencia;

public:
	Elemento() {}
	Elemento(int n) {
		alto = 30;
		ancho = 30;
		this->n = n;
		punto = Point(0, 0);
	}
	void dibujar(Graphics^ g) {
		Pen^ p = gcnew Pen(Color::Black);
		Font^ miFuente = gcnew Font("Arial", 12);
		g->DrawString(n.ToString(), miFuente, Brushes::Black, punto.X + 4, punto.Y + 7);
	}

	Point getPunto() {	return punto;}
	void setPunto(int x, int y) {punto = Point(x, y);}
	Rectangle getrec() {return Rectangle(punto.X, punto.Y, ancho, alto);}
	void setCorrespondencia(int correspondencia) {this->correspondencia = correspondencia;}
	int getCorrespondencia() {return correspondencia;}
	int getN() {return n;}
};

