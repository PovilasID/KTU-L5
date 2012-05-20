// L5.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "Employee.h"
#include "Company.h"
#include "Workers.h"
#include "PriceList.h"


using namespace L5;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
