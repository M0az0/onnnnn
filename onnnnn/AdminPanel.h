#pragma once
#include "Models.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace SimpleStore {

    public ref class AdminPanel : public Form {
    private:
        List<Product^>^ products;
        ListBox^ listProducts;
        TextBox^ txtName;
        TextBox^ txtPrice;
        NumericUpDown^ numStock;
        Button^ btnAdd;
        Button^ btnUpdate;
        Button^ btnDelete;
        Button^ btnClose;
        int selectedProductId;

    public:
        AdminPanel(List<Product^>^ productList) {
            products = productList;
            selectedProductId = -1;
            InitializeUI();
            LoadProducts();
        }

    private:
        void InitializeUI() {
            this->Text = L"🔧 Admin Panel - لوحة تحكم الأدمن";
            this->Size = System::Drawing::Size(900, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;

            // Header Panel
            Panel^ panelHeader = gcnew Panel();
            panelHeader->Dock = DockStyle::Top;
            panelHeader->Height = 70;
            panelHeader->BackColor = Color::FromArgb(156, 39, 176);
            this->Controls->Add(panelHeader);

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"🔧 Admin Control Panel";
            lblTitle->Font = gcnew System::Drawing::Font(L"Arial", 20, FontStyle::Bold);
            lblTitle->ForeColor = Color::White;
            lblTitle->Location = Point(20, 20);
            lblTitle->AutoSize = true;
            panelHeader->Controls->Add(lblTitle);

            // Products List
            Label^ lblProducts = gcnew Label();
            lblProducts->Text = L"📦 Current Products - المنتجات الحالية";
            lblProducts->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
            lblProducts->Location = Point(20, 90);
            lblProducts->Size = System::Drawing::Size(400, 25);
            lblProducts->ForeColor = Color::FromArgb(156, 39, 176);
            this->Controls->Add(lblProducts);

            listProducts = gcnew ListBox();
            listProducts->Location = Point(20, 120);
            listProducts->Size = System::Drawing::Size(400, 380);
            listProducts->Font = gcnew System::Drawing::Font(L"Courier New", 10);
            listProducts->BackColor = Color::FromArgb(250, 250, 250);
            listProducts->SelectedIndexChanged += gcnew EventHandler(this, &AdminPanel::listProducts_SelectedIndexChanged);
            this->Controls->Add(listProducts);

            // Product Form Panel
            Panel^ panelForm = gcnew Panel();
            panelForm->Location = Point(440, 90);
            panelForm->Size = System::Drawing::Size(430, 410);
            panelForm->BackColor = Color::FromArgb(245, 245, 245);
            panelForm->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->Controls->Add(panelForm);

            Label^ lblFormTitle = gcnew Label();
            lblFormTitle->Text = L"➕ Add / Edit Product";
            lblFormTitle->Font = gcnew System::Drawing::Font(L"Arial", 14, FontStyle::Bold);
            lblFormTitle->Location = Point(15, 15);
            lblFormTitle->Size = System::Drawing::Size(400, 30);
            lblFormTitle->ForeColor = Color::FromArgb(156, 39, 176);
            panelForm->Controls->Add(lblFormTitle);

            // Product Name
            Label^ lblName = gcnew Label();
            lblName->Text = L"Product Name - اسم المنتج:";
            lblName->Location = Point(15, 60);
            lblName->Size = System::Drawing::Size(400, 25);
            lblName->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
            panelForm->Controls->Add(lblName);

            txtName = gcnew TextBox();
            txtName->Location = Point(15, 90);
            txtName->Size = System::Drawing::Size(400, 30);
            txtName->Font = gcnew System::Drawing::Font(L"Arial", 12);
            panelForm->Controls->Add(txtName);

            // Price
            Label^ lblPrice = gcnew Label();
            lblPrice->Text = L"Price ($) - السعر:";
            lblPrice->Location = Point(15, 140);
            lblPrice->Size = System::Drawing::Size(400, 25);
            lblPrice->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
            panelForm->Controls->Add(lblPrice);

            txtPrice = gcnew TextBox();
            txtPrice->Location = Point(15, 170);
            txtPrice->Size = System::Drawing::Size(400, 30);
            txtPrice->Font = gcnew System::Drawing::Font(L"Arial", 12);
            panelForm->Controls->Add(txtPrice);

            // Stock
            Label^ lblStock = gcnew Label();
            lblStock->Text = L"Stock Quantity - الكمية:";
            lblStock->Location = Point(15, 220);
            lblStock->Size = System::Drawing::Size(400, 25);
            lblStock->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
            panelForm->Controls->Add(lblStock);

            numStock = gcnew NumericUpDown();
            numStock->Location = Point(15, 250);
            numStock->Size = System::Drawing::Size(400, 30);
            numStock->Font = gcnew System::Drawing::Font(L"Arial", 12);
            numStock->Minimum = 0;
            numStock->Maximum = 10000;
            numStock->Value = 0;
            panelForm->Controls->Add(numStock);

            // Buttons
            btnAdd = gcnew Button();
            btnAdd->Text = L"➕ Add Product";
            btnAdd->Location = Point(15, 300);
            btnAdd->Size = System::Drawing::Size(195, 45);
            btnAdd->BackColor = Color::FromArgb(76, 175, 80);
            btnAdd->ForeColor = Color::White;
            btnAdd->FlatStyle = FlatStyle::Flat;
            btnAdd->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnAdd->Click += gcnew EventHandler(this, &AdminPanel::btnAdd_Click);
            panelForm->Controls->Add(btnAdd);

            btnUpdate = gcnew Button();
            btnUpdate->Text = L"✏️ Update";
            btnUpdate->Location = Point(220, 300);
            btnUpdate->Size = System::Drawing::Size(195, 45);
            btnUpdate->BackColor = Color::FromArgb(33, 150, 243);
            btnUpdate->ForeColor = Color::White;
            btnUpdate->FlatStyle = FlatStyle::Flat;
            btnUpdate->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnUpdate->Click += gcnew EventHandler(this, &AdminPanel::btnUpdate_Click);
            btnUpdate->Enabled = false;
            panelForm->Controls->Add(btnUpdate);

            btnDelete = gcnew Button();
            btnDelete->Text = L"🗑️ Delete Product";
            btnDelete->Location = Point(15, 355);
            btnDelete->Size = System::Drawing::Size(400, 45);
            btnDelete->BackColor = Color::FromArgb(244, 67, 54);
            btnDelete->ForeColor = Color::White;
            btnDelete->FlatStyle = FlatStyle::Flat;
            btnDelete->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnDelete->Click += gcnew EventHandler(this, &AdminPanel::btnDelete_Click);
            btnDelete->Enabled = false;
            panelForm->Controls->Add(btnDelete);

            // Close Button
            btnClose = gcnew Button();
            btnClose->Text = L"✖ Close";
            btnClose->Location = Point(440, 510);
            btnClose->Size = System::Drawing::Size(430, 45);
            btnClose->BackColor = Color::Gray;
            btnClose->ForeColor = Color::White;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnClose->Click += gcnew EventHandler(this, &AdminPanel::btnClose_Click);
            this->Controls->Add(btnClose);
        }

        void LoadProducts() {
            listProducts->Items->Clear();
            for each (Product ^ p in products) {
                listProducts->Items->Add(p->ToString());
            }
        }

        void listProducts_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            if (listProducts->SelectedIndex >= 0) {
                Product^ selected = products[listProducts->SelectedIndex];
                selectedProductId = selected->Id;

                txtName->Text = selected->Name;
                txtPrice->Text = selected->Price.ToString();
                numStock->Value = selected->Stock;

                btnUpdate->Enabled = true;
                btnDelete->Enabled = true;
            }
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtName->Text)) {
                MessageBox::Show(L"Please enter product name!\nالرجاء إدخال اسم المنتج!",
                    L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show(L"Please enter valid price!\nالرجاء إدخال سعر صحيح!",
                    L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            int newId = 1;
            if (products->Count > 0) {
                for each (Product ^ p in products) {
                    if (p->Id >= newId) newId = p->Id + 1;
                }
            }

            Product^ newProduct = gcnew Product(newId, txtName->Text, price, (int)numStock->Value);
            products->Add(newProduct);

            LoadProducts();
            ClearForm();

            MessageBox::Show(L"✓ Product added successfully!\nتمت إضافة المنتج بنجاح!",
                L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnUpdate_Click(Object^ sender, EventArgs^ e) {
            if (selectedProductId == -1) return;

            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show(L"Please enter valid price!\nالرجاء إدخال سعر صحيح!",
                    L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            for each (Product ^ p in products) {
                if (p->Id == selectedProductId) {
                    p->Name = txtName->Text;
                    p->Price = price;
                    p->Stock = (int)numStock->Value;
                    break;
                }
            }

            LoadProducts();
            ClearForm();

            MessageBox::Show(L"✓ Product updated successfully!\nتم تحديث المنتج بنجاح!",
                L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e) {
            if (selectedProductId == -1) return;

            auto result = MessageBox::Show(
                L"Are you sure you want to delete this product?\nهل تريد حذف هذا المنتج؟",
                L"Confirm Delete",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                for (int i = 0; i < products->Count; i++) {
                    if (products[i]->Id == selectedProductId) {
                        products->RemoveAt(i);
                        break;
                    }
                }

                LoadProducts();
                ClearForm();

                MessageBox::Show(L"✓ Product deleted successfully!\nتم حذف المنتج بنجاح!",
                    L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnClose_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }

        void ClearForm() {
            txtName->Clear();
            txtPrice->Clear();
            numStock->Value = 0;
            selectedProductId = -1;
            btnUpdate->Enabled = false;
            btnDelete->Enabled = false;
            listProducts->ClearSelected();
        }
    };
}
