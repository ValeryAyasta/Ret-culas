#pragma once
#include "Diagrama.h"

namespace Reticula {

	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;

	public ref class FormReticula : public Form
	{
		Timer^ timer1;
		IContainer^ components;
		CConjunto* conjunto;
		Diagrama* d;
		Validaciones* OP;

	public:
		FormReticula(CConjunto* conjunto, Validaciones* OP) {
			InitializeComponent();
			this->conjunto = conjunto;
			this->OP = OP;
			d = new Diagrama(conjunto, OP);}

		Diagrama* getDiagrama() {	return d;}

	protected:
		~FormReticula() {if (components){	delete components;}}

#pragma region Windows Form Designer generated code
		void InitializeComponent()
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew Timer(this->components));
			timer1->Enabled = true;

			this->timer1->Tick += gcnew System::EventHandler(this, &FormReticula::timer1_Tick);
			this->StartPosition = FormStartPosition::CenterScreen;
		}

#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		Graphics^ g;
		BufferedGraphicsContext^ espacio;
		BufferedGraphics^ buffer;

		g = this->CreateGraphics();
		espacio = BufferedGraphicsManager::Current;
		buffer = espacio->Allocate(g, this->ClientRectangle);

		buffer->Graphics->Clear(Color::White);
		d->dibujarDiagrama(buffer->Graphics);

		buffer->Render(g);
		delete buffer;
		delete espacio;
		delete g;
	}
	};
}