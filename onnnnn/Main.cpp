#include "mainform.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

   
    SimpleStore::StoreForm^ store = gcnew SimpleStore::StoreForm();
    Application::Run(store);

    return 0;
}