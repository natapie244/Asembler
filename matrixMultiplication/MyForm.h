#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <msclr\marshal_cppstd.h>
//#include <stdafx.h>


struct matrixInfo
{
	bool isValid;
	int row;
	int colums;
};

double * vectorToArray(std::vector<std::vector<double>> matrixA);
std::vector<std::vector<double>> loadFile(std::string filename);
matrixInfo getMatrixInfo(std::vector<std::vector<double>>);
void multiplyMatrix(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB);
void cppMatrixMultiplication(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB);
void asmMatrixMultiplication(std::vector<std::vector<double>> matrixA, std::vector<std::vector<double>> matrixB);
matrixInfo matrixAInfo = { false, 0, 0 };
matrixInfo matrixBInfo = { false, 0, 0 };


std::vector<std::vector<double>> matrixA;
std::vector<std::vector<double>> matrixB;


namespace matrixMultiplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  chooseMatrixAButton;
	private: System::Windows::Forms::Button^  chooseMatrixBButton;
	private: System::Windows::Forms::Label^  matrixADimensions;
	private: System::Windows::Forms::Label^  matrixBDimensions;
	private: System::Windows::Forms::GroupBox^  libraryBox;
	private: System::Windows::Forms::RadioButton^  asmRadio;
	private: System::Windows::Forms::RadioButton^  CRadio;
	private: System::Windows::Forms::GroupBox^  operationBox;
	private: System::Windows::Forms::RadioButton^  BxARadio;
	private: System::Windows::Forms::RadioButton^  AxBRadio;
	private: System::Windows::Forms::Button^  confirmButton;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::TextBox^  ASourceText;
	private: System::Windows::Forms::TextBox^  BSourceText;
	private: System::Windows::Forms::Button^  confirmAButton;
	private: System::Windows::Forms::Button^  confirmBButton;
	protected:


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->chooseMatrixAButton = (gcnew System::Windows::Forms::Button());
			this->chooseMatrixBButton = (gcnew System::Windows::Forms::Button());
			this->matrixADimensions = (gcnew System::Windows::Forms::Label());
			this->matrixBDimensions = (gcnew System::Windows::Forms::Label());
			this->libraryBox = (gcnew System::Windows::Forms::GroupBox());
			this->asmRadio = (gcnew System::Windows::Forms::RadioButton());
			this->CRadio = (gcnew System::Windows::Forms::RadioButton());
			this->operationBox = (gcnew System::Windows::Forms::GroupBox());
			this->BxARadio = (gcnew System::Windows::Forms::RadioButton());
			this->AxBRadio = (gcnew System::Windows::Forms::RadioButton());
			this->confirmButton = (gcnew System::Windows::Forms::Button());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ASourceText = (gcnew System::Windows::Forms::TextBox());
			this->BSourceText = (gcnew System::Windows::Forms::TextBox());
			this->confirmAButton = (gcnew System::Windows::Forms::Button());
			this->confirmBButton = (gcnew System::Windows::Forms::Button());
			this->libraryBox->SuspendLayout();
			this->operationBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// chooseMatrixAButton
			// 
			this->chooseMatrixAButton->Location = System::Drawing::Point(34, 34);
			this->chooseMatrixAButton->Name = L"chooseMatrixAButton";
			this->chooseMatrixAButton->Size = System::Drawing::Size(104, 34);
			this->chooseMatrixAButton->TabIndex = 0;
			this->chooseMatrixAButton->Text = L"Wczytaj macierz A";
			this->chooseMatrixAButton->UseVisualStyleBackColor = true;
			this->chooseMatrixAButton->Click += gcnew System::EventHandler(this, &MyForm::chooseMatrixAButton_Click);
			// 
			// chooseMatrixBButton
			// 
			this->chooseMatrixBButton->Location = System::Drawing::Point(34, 95);
			this->chooseMatrixBButton->Name = L"chooseMatrixBButton";
			this->chooseMatrixBButton->Size = System::Drawing::Size(104, 34);
			this->chooseMatrixBButton->TabIndex = 1;
			this->chooseMatrixBButton->Text = L"Wczytaj macierz B";
			this->chooseMatrixBButton->UseVisualStyleBackColor = true;
			this->chooseMatrixBButton->Click += gcnew System::EventHandler(this, &MyForm::chooseMatrixBButton_Click);
			// 
			// matrixADimensions
			// 
			this->matrixADimensions->AutoSize = true;
			this->matrixADimensions->Location = System::Drawing::Point(37, 71);
			this->matrixADimensions->Name = L"matrixADimensions";
			this->matrixADimensions->Size = System::Drawing::Size(101, 13);
			this->matrixADimensions->TabIndex = 2;
			this->matrixADimensions->Text = L"Wymiary macierzy A";
			// 
			// matrixBDimensions
			// 
			this->matrixBDimensions->AutoSize = true;
			this->matrixBDimensions->Location = System::Drawing::Point(37, 132);
			this->matrixBDimensions->Name = L"matrixBDimensions";
			this->matrixBDimensions->Size = System::Drawing::Size(101, 13);
			this->matrixBDimensions->TabIndex = 3;
			this->matrixBDimensions->Text = L"Wymiary macierzy B";
			// 
			// libraryBox
			// 
			this->libraryBox->Controls->Add(this->asmRadio);
			this->libraryBox->Controls->Add(this->CRadio);
			this->libraryBox->Location = System::Drawing::Point(34, 170);
			this->libraryBox->Name = L"libraryBox";
			this->libraryBox->Size = System::Drawing::Size(138, 86);
			this->libraryBox->TabIndex = 4;
			this->libraryBox->TabStop = false;
			this->libraryBox->Text = L"Wybierz bilbiotekê";
			// 
			// asmRadio
			// 
			this->asmRadio->AutoSize = true;
			this->asmRadio->Location = System::Drawing::Point(6, 42);
			this->asmRadio->Name = L"asmRadio";
			this->asmRadio->Size = System::Drawing::Size(68, 17);
			this->asmRadio->TabIndex = 1;
			this->asmRadio->TabStop = true;
			this->asmRadio->Text = L"Asembler";
			this->asmRadio->UseVisualStyleBackColor = true;
			// 
			// CRadio
			// 
			this->CRadio->AutoSize = true;
			this->CRadio->Location = System::Drawing::Point(6, 19);
			this->CRadio->Name = L"CRadio";
			this->CRadio->Size = System::Drawing::Size(44, 17);
			this->CRadio->TabIndex = 0;
			this->CRadio->TabStop = true;
			this->CRadio->Text = L"C++";
			this->CRadio->UseVisualStyleBackColor = true;
			// 
			// operationBox
			// 
			this->operationBox->Controls->Add(this->BxARadio);
			this->operationBox->Controls->Add(this->AxBRadio);
			this->operationBox->Location = System::Drawing::Point(217, 170);
			this->operationBox->Name = L"operationBox";
			this->operationBox->Size = System::Drawing::Size(138, 86);
			this->operationBox->TabIndex = 5;
			this->operationBox->TabStop = false;
			this->operationBox->Text = L"Wybierz dzia³anie";
			// 
			// BxARadio
			// 
			this->BxARadio->AutoSize = true;
			this->BxARadio->Enabled = false;
			this->BxARadio->Location = System::Drawing::Point(6, 42);
			this->BxARadio->Name = L"BxARadio";
			this->BxARadio->Size = System::Drawing::Size(50, 17);
			this->BxARadio->TabIndex = 1;
			this->BxARadio->TabStop = true;
			this->BxARadio->Text = L"B x A";
			this->BxARadio->UseVisualStyleBackColor = true;
			// 
			// AxBRadio
			// 
			this->AxBRadio->AutoSize = true;
			this->AxBRadio->Enabled = false;
			this->AxBRadio->Location = System::Drawing::Point(6, 19);
			this->AxBRadio->Name = L"AxBRadio";
			this->AxBRadio->Size = System::Drawing::Size(50, 17);
			this->AxBRadio->TabIndex = 0;
			this->AxBRadio->TabStop = true;
			this->AxBRadio->Text = L"A x B";
			this->AxBRadio->UseVisualStyleBackColor = true;
			// 
			// confirmButton
			// 
			this->confirmButton->Location = System::Drawing::Point(102, 281);
			this->confirmButton->Name = L"confirmButton";
			this->confirmButton->Size = System::Drawing::Size(171, 56);
			this->confirmButton->TabIndex = 6;
			this->confirmButton->Text = L"ZatwierdŸ";
			this->confirmButton->UseVisualStyleBackColor = true;
			this->confirmButton->Click += gcnew System::EventHandler(this, &MyForm::confirmButton_Click);
			// 
			// openFileDialog
			// 
			this->openFileDialog->InitialDirectory = L"openFileDialog";
			// 
			// ASourceText
			// 
			this->ASourceText->Location = System::Drawing::Point(146, 42);
			this->ASourceText->Name = L"ASourceText";
			this->ASourceText->Size = System::Drawing::Size(174, 20);
			this->ASourceText->TabIndex = 7;
			// 
			// BSourceText
			// 
			this->BSourceText->Location = System::Drawing::Point(146, 103);
			this->BSourceText->Name = L"BSourceText";
			this->BSourceText->Size = System::Drawing::Size(174, 20);
			this->BSourceText->TabIndex = 8;
			// 
			// confirmAButton
			// 
			this->confirmAButton->Location = System::Drawing::Point(337, 38);
			this->confirmAButton->Name = L"confirmAButton";
			this->confirmAButton->Size = System::Drawing::Size(98, 27);
			this->confirmAButton->TabIndex = 9;
			this->confirmAButton->Text = L"ZatwierdŸ";
			this->confirmAButton->UseVisualStyleBackColor = true;
			this->confirmAButton->Click += gcnew System::EventHandler(this, &MyForm::confirmAButton_Click);
			// 
			// confirmBButton
			// 
			this->confirmBButton->Location = System::Drawing::Point(337, 99);
			this->confirmBButton->Name = L"confirmBButton";
			this->confirmBButton->Size = System::Drawing::Size(98, 27);
			this->confirmBButton->TabIndex = 10;
			this->confirmBButton->Text = L"ZatwierdŸ";
			this->confirmBButton->UseVisualStyleBackColor = true;
			this->confirmBButton->Click += gcnew System::EventHandler(this, &MyForm::confirmBButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(466, 360);
			this->Controls->Add(this->confirmBButton);
			this->Controls->Add(this->confirmAButton);
			this->Controls->Add(this->BSourceText);
			this->Controls->Add(this->ASourceText);
			this->Controls->Add(this->confirmButton);
			this->Controls->Add(this->operationBox);
			this->Controls->Add(this->libraryBox);
			this->Controls->Add(this->matrixBDimensions);
			this->Controls->Add(this->matrixADimensions);
			this->Controls->Add(this->chooseMatrixBButton);
			this->Controls->Add(this->chooseMatrixAButton);
			this->Name = L"MyForm";
			this->Text = L"Mno¿enie Macierzy";
			this->libraryBox->ResumeLayout(false);
			this->libraryBox->PerformLayout();
			this->operationBox->ResumeLayout(false);
			this->operationBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		private: System::Void chooseMatrixAButton_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialog->ShowDialog();
			ASourceText->Text = openFileDialog->FileName;
		}

		private: System::Void confirmAButton_Click(System::Object^  sender, System::EventArgs^  e) {

			System::String^ managedString = ASourceText->Text;
			msclr::interop::marshal_context context;
			std::string standardString = context.marshal_as<std::string>(managedString);

			matrixA = loadFile(standardString);
			matrixAInfo = getMatrixInfo(matrixA); 
			matrixADimensions->Text = matrixAInfo.row.ToString() + "x" + matrixAInfo.colums.ToString();
			setButtons();
		};

		private: System::Void setButtons() {
			if (matrixAInfo.isValid == true && matrixBInfo.isValid == true) {
				if (matrixAInfo.colums == matrixBInfo.row) {
					AxBRadio->Enabled = true;
				}
				else {
					AxBRadio->Enabled = false;
				}

				if (matrixBInfo.colums == matrixAInfo.row) {
					BxARadio->Enabled = true;
				}
				else {
					BxARadio->Enabled = false;
				}
				
			}
			else {
				BxARadio->Enabled = false;
				AxBRadio->Enabled = false;
			}
		}

		private: System::Void confirmBButton_Click(System::Object^  sender, System::EventArgs^  e) {
			System::String^ managedString = BSourceText->Text;
			msclr::interop::marshal_context context;
			std::string standardString = context.marshal_as<std::string>(managedString);

			matrixB = loadFile(standardString);
			matrixBInfo = getMatrixInfo(matrixB);
			matrixBDimensions->Text = matrixBInfo.row.ToString() + "x" + matrixBInfo.colums.ToString();

			setButtons();
		}
		private: System::Void chooseMatrixBButton_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialog->ShowDialog();
			BSourceText->Text = openFileDialog->FileName;
		}
	private: System::Void confirmButton_Click(System::Object^  sender, System::EventArgs^  e) {
		//multiplyMatrix(matrixA, matrixB);

		//cppMatrixMultiplication(matrixA, matrixB); 
			///to ju¿ dzia³a na intach, do przerobienia na double
		asmMatrixMultiplication(matrixA, matrixB);


		//vectorToArray(matrixA);
	}
};
}
