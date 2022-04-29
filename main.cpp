#include "FormReticula.h"
#include "Validaciones.h"
#include "CComprobar.h"
using namespace Reticula;

void main() {

	srand(time(NULL));
	int n;
	CConjunto* objconjunto;
	cout << "\t RETICULAS \t";
	cout << endl;
	cout << endl;
	do
	{
		cout << "introduce la cantidad de elementos del conjunto: "; cin >> n;
	} while (n < 4 || n>10);

	system("CLS");

	objconjunto = new CConjunto(n);
	int e;
	for (int i = 0; i < n; i++)
	{
		cout << "introduce elemento n" << i + 1 << ": ";
		cin >> e;
		objconjunto->agregarelemento(e);
	}

	objconjunto->mostrar();
	system("pause");

	system("CLS");
	//validaciones
	Validaciones* orden_parcial;

	cout << "1. Generar relacion aleatoriamente" << endl;
	cout << "2. Ingresar matriz" << endl;

	int opcion;
	cout << "Opcion: ";
	cin >> opcion;

	if (opcion == 1) {
		orden_parcial = new Validaciones(objconjunto);
		cout << "A continuacion, se muestra la MATRIZ DE RELACION" << endl;

		orden_parcial->mostrar_matriz();
		system("pause");
	}
	else {
		bool** matriz = new bool* [n];
		for (int i = 0; i < n; i++) { matriz[i] = new bool[n]; }

		cout << "\nMR: " << endl;
		cout << "   ";
		for (int i = 0; i < n; i++) { cout << objconjunto->getVector()[i] << " "; }
		cout << endl;

		for (int i = 0; i < n; i++) {
			int espacio = 0;
			cout << objconjunto->getVector()[i] << " ";

			for (int j = 0; j < n; j++) {

				Console::ForegroundColor = ConsoleColor::Blue;
				Console::SetCursorPosition(3 + espacio, 6 + i);

				cin >> matriz[i][j];
				cout << " ";

				espacio = espacio + 2;
				Console::ForegroundColor = ConsoleColor::White;
			}
			cout << endl;
		}
		cout << endl;

		orden_parcial = new Validaciones(objconjunto, matriz);
		system("CLS");
	}

	if (orden_parcial->EsOrdenParcial()) {

		cout << "LA RELACION ES DE ORDEN PARCIAL" << endl;
		cout << endl;

		system("pause");
		system("CLS");

		FormReticula^ grafico = gcnew FormReticula(objconjunto, orden_parcial);


		cout << "COMPROBANDO SI LA RELACION ES UNA RETICULA..." << endl;

		CComprobar* comprobacion_reticula = new CComprobar(objconjunto, orden_parcial->getMatrizRelacion(), objconjunto->getN(), grafico->getDiagrama());

		if (comprobacion_reticula->Comprobar_Reticula()) {
			cout << "LA RELACION SI ES UNA RETICULA." << endl;
			cout << "A continuación se muestran los complementos: " << endl;
			comprobacion_reticula->Complemento_Reticula();

		}
		else { cout << "La relacion NO es una reticula." << endl; }
		Application::Run(grafico);

	}
	else {
		cout << "La relacion NO es de orden parcial" << endl;
		system("pause");
	}
}