#pragma once
#include "LISTS.h"

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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(572, 310);
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

			 }
	};
}

