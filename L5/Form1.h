#pragma once
#include "LISTS.h"
#include <stdio.h>
#include <fstream>

namespace L5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(118, 9);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(117, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Pasirinkti aplanka...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 11);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"*.txt";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(241, 8);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Pasirinkti faila...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(12, 37);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(548, 261);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(572, 310);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1 = gcnew System::Windows::Forms::FolderBrowserDialog();
				if (textBox1->Text == L"") {
				MessageBox::Show (L"�ra�ykite �ablon�", L"Ne�vesta reik�m�", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
				}

				if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && folderBrowserDialog1->SelectedPath ->Length > 0) {
				//listBox1->Items->Clear();             // I�valome listBox1 komponent�

				WIN32_FIND_DATA ffd;                  // Paie�kai reikalingi ...
				HANDLE hFind = INVALID_HANDLE_VALUE;  // ... tarnybiniai kintamieji

				// Funkcijai PtrToStringChars() reikalingas #include <vcclr.h>
				pin_ptr<const wchar_t> pletinys = PtrToStringChars(textBox1->Text);

				TCHAR katalogas[MAX_PATH];        // Saugosime keli� iki duomen� fail�
				TCHAR paieskosSablonas[MAX_PATH]; // Saugosime paie�kos �ablon�
				TCHAR pilnasVardas[MAX_PATH];     // Saugosime konkretaus duomen� failo piln� (su keliu) vard�

				// Sudarome keli� � katalog�, kuriame sud�ti duomen� failai
				pin_ptr<const wchar_t> pasirinktasKatalogas = PtrToStringChars(folderBrowserDialog1->SelectedPath);
				StringCchCopy(katalogas, MAX_PATH, pasirinktasKatalogas);
				StringCchCat(katalogas, MAX_PATH, TEXT("\\"));
				//label1->Text = gcnew String(katalogas);

				// Sudarome paie�kos �ablon�
				StringCchCopy(paieskosSablonas, MAX_PATH, katalogas);
				StringCchCat(paieskosSablonas, MAX_PATH, pletinys);

				// Atliekame paie�k�
				hFind = FindFirstFile(paieskosSablonas, &ffd);
				if (hFind == INVALID_HANDLE_VALUE) { // Tikriname, gal n�ra nei vieno �ablon� atitinkan�io failo
					//listBox1->Items->Add(gcnew String(L"�ablon� atitinkan�i� fail� nerasta."));
					return;
				}
				do {
					// Sudarome piln� (su keliu) rasto duomen� failo vard�
					StringCchCopy(pilnasVardas, MAX_PATH, katalogas);
					StringCchCat(pilnasVardas, MAX_PATH, ffd.cFileName);
                 
					// naudojame failo vard�, kuris saugomas kintamajame pilnasVardas,
					// pavyzd�iui, ifstream fd(pilnasVardas);

					// �ioje programoje tiesiog i�vedame listBox1 komponente
					//listBox1->Items->Add(String::Format(L"{0}", gcnew String(pilnasVardas)));
					editCompany().Read(SysStrToStr(gcnew String(pilnasVardas)));

				} while (FindNextFile(hFind, &ffd) != 0);
				FindClose(hFind);
				}

				//*************************ADD PORTECTION FROM DOUBLES , CREATE FILE CONSTANTS******************************
				ofstream fc("Results.txt");
				if (fc.good()){
					fc << "";
					fc.close();
				}
				getCompany().Otput("Results.txt");
				setWorkers(&getCompany().CompanyToWorkers());
				getWorkers().output("Results.txt");

				richTextBox1->LoadFile("Results.txt", RichTextBoxStreamType::PlainText);
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			  IO::Stream^ myStream;
			  OpenFileDialog^ openFileDialogPrices = gcnew OpenFileDialog;

			  openFileDialogPrices->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
			  openFileDialogPrices->FilterIndex = 2;
			  openFileDialogPrices->RestoreDirectory = true;

			  if ( openFileDialogPrices->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
				if ( (myStream = openFileDialogPrices->OpenFile()) != nullptr ){
					//setRecipesFile(openFileDialogPrices->FileName);
					//if(getOrdersFile() != nullptr){
						//button1->Enabled = true;
					//}
					editPriceList().read(SysStrToStr(openFileDialogPrices->FileName));
					getPriceList().output("Results.txt");
                  myStream->Close();
				}
			  }
			 }
};
}

