#pragma once
#include "Models.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace SimpleStore {

    public ref class StoreForm : public Form {
    private:
        List<Product^>^ products;
        List<CartItem^>^ cart;
        String^ currentUser;

        Panel^ panelTop;
        Label^ lblTitle;
        Label^ lblUser;
        Button^ btnLogin;
        ListBox^ listProducts;
        ListBox^ listCart;
        Label^ lblTotal;
        NumericUpDown^ numQuantity;
        Button^ btnAddToCart;
        Button^ btnCheckout;
        Button^ btnClearCart;
        Label^ lblProductsTitle;
        Label^ lblCartTitle;

    public:
        StoreForm() {
            InitializeData();
            InitializeUI();
        }

    private:
        void InitializeData() {
            products = gcnew List<Product^>();
            cart = gcnew List<CartItem^>();
            currentUser = "Guest";

            products->Add(gcnew Product(1, "Laptop Dell", 1299.99, 10));
            products->Add(gcnew Product(2, "iPhone 15", 999.99, 15));
            products->Add(gcnew Product(3, "Samsung TV", 699.99, 8));
            products->Add(gcnew Product(4, "Headphones", 299.99, 20));
            products->Add(gcnew Product(5, "Office Chair", 249.99, 12));
            products->Add(gcnew Product(6, "Gaming Mouse", 79.99, 25));
            products->Add(gcnew Product(7, "Keyboard", 149.99, 18));
            products->Add(gcnew Product(8, "Monitor 27\"", 399.99, 10));
        }

        void InitializeUI() {
            this->Text = L"🛒 Simple Store - متجر بسيط";
            this->Size = System::Drawing::Size(1000, 650);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;

            panelTop = gcnew Panel();
            panelTop->Dock = DockStyle::Top;
            panelTop->Height = 80;
            panelTop->BackColor = Color::FromArgb(33, 150, 243);
            this->Controls->Add(panelTop);

            lblTitle = gcnew Label();
            lblTitle->Text = L"🛒 Simple Online Store";
            lblTitle->Font = gcnew System::Drawing::Font(L"Arial", 22, FontStyle::Bold);
            lblTitle->ForeColor = Color::White;
            lblTitle->Location = Point(20, 20);
            lblTitle->AutoSize = true;
            panelTop->Controls->Add(lblTitle);

            lblUser = gcnew Label();
            lblUser->Text = L"👤 Guest";
            lblUser->Font = gcnew System::Drawing::Font(L"Arial", 12);
            lblUser->ForeColor = Color::White;
            lblUser->Location = Point(720, 25);
            lblUser->Size = System::Drawing::Size(150, 30);
            panelTop->Controls->Add(lblUser);

            btnLogin = gcnew Button();
            btnLogin->Text = L"Login";
            btnLogin->Location = Point(880, 20);
            btnLogin->Size = System::Drawing::Size(90, 40);
            btnLogin->BackColor = Color::FromArgb(76, 175, 80);
            btnLogin->ForeColor = Color::White;
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnLogin->Click += gcnew EventHandler(this, &StoreForm::btnLogin_Click);
            panelTop->Controls->Add(btnLogin);

            lblProductsTitle = gcnew Label();
            lblProductsTitle->Text = L"📦 Available Products - المنتجات المتاحة";
            lblProductsTitle->Font = gcnew System::Drawing::Font(L"Arial", 14, FontStyle::Bold);
            lblProductsTitle->Location = Point(20, 100);
            lblProductsTitle->Size = System::Drawing::Size(450, 30);
            lblProductsTitle->ForeColor = Color::FromArgb(33, 150, 243);
            this->Controls->Add(lblProductsTitle);

            listProducts = gcnew ListBox();
            listProducts->Location = Point(20, 140);
            listProducts->Size = System::Drawing::Size(450, 350);
            listProducts->Font = gcnew System::Drawing::Font(L"Courier New", 10);
            listProducts->BackColor = Color::FromArgb(250, 250, 250);
            this->Controls->Add(listProducts);

            LoadProducts();

            Label^ lblQty = gcnew Label();
            lblQty->Text = L"Quantity:";
            lblQty->Location = Point(20, 505);
            lblQty->Size = System::Drawing::Size(80, 25);
            lblQty->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
            this->Controls->Add(lblQty);

            numQuantity = gcnew NumericUpDown();
            numQuantity->Location = Point(110, 502);
            numQuantity->Size = System::Drawing::Size(70, 30);
            numQuantity->Font = gcnew System::Drawing::Font(L"Arial", 12);
            numQuantity->Minimum = 1;
            numQuantity->Maximum = 100;
            numQuantity->Value = 1;
            this->Controls->Add(numQuantity);

            btnAddToCart = gcnew Button();
            btnAddToCart->Text = L"🛒 Add to Cart";
            btnAddToCart->Location = Point(200, 500);
            btnAddToCart->Size = System::Drawing::Size(270, 40);
            btnAddToCart->BackColor = Color::FromArgb(76, 175, 80);
            btnAddToCart->ForeColor = Color::White;
            btnAddToCart->FlatStyle = FlatStyle::Flat;
            btnAddToCart->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
            btnAddToCart->Click += gcnew EventHandler(this, &StoreForm::btnAddToCart_Click);
            this->Controls->Add(btnAddToCart);

            lblCartTitle = gcnew Label();
            lblCartTitle->Text = L"🛒 Shopping Cart - سلة التسوق";
            lblCartTitle->Font = gcnew System::Drawing::Font(L"Arial", 14, FontStyle::Bold);
            lblCartTitle->Location = Point(510, 100);
            lblCartTitle->Size = System::Drawing::Size(450, 30);
            lblCartTitle->ForeColor = Color::FromArgb(255, 152, 0);
            this->Controls->Add(lblCartTitle);

            listCart = gcnew ListBox();
            listCart->Location = Point(510, 140);
            listCart->Size = System::Drawing::Size(450, 300);
            listCart->Font = gcnew System::Drawing::Font(L"Courier New", 10);
            listCart->BackColor = Color::FromArgb(255, 250, 240);
            this->Controls->Add(listCart);

            lblTotal = gcnew Label();
            lblTotal->Text = L"💰 Total: $0.00";
            lblTotal->Font = gcnew System::Drawing::Font(L"Arial", 16, FontStyle::Bold);
            lblTotal->Location = Point(510, 450);
            lblTotal->Size = System::Drawing::Size(450, 35);
            lblTotal->ForeColor = Color::FromArgb(76, 175, 80);
            lblTotal->TextAlign = ContentAlignment::MiddleRight;
            this->Controls->Add(lblTotal);

            btnCheckout = gcnew Button();
            btnCheckout->Text = L"✓ Checkout";
            btnCheckout->Location = Point(510, 500);
            btnCheckout->Size = System::Drawing::Size(220, 40);
            btnCheckout->BackColor = Color::FromArgb(33, 150, 243);
            btnCheckout->ForeColor = Color::White;
            btnCheckout->FlatStyle = FlatStyle::Flat;
            btnCheckout->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
            btnCheckout->Click += gcnew EventHandler(this, &StoreForm::btnCheckout_Click);
            this->Controls->Add(btnCheckout);

            btnClearCart = gcnew Button();
            btnClearCart->Text = L"🗑️ Clear";
            btnClearCart->Location = Point(740, 500);
            btnClearCart->Size = System::Drawing::Size(220, 40);
            btnClearCart->BackColor = Color::FromArgb(244, 67, 54);
            btnClearCart->ForeColor = Color::White;
            btnClearCart->FlatStyle = FlatStyle::Flat;
            btnClearCart->Font = gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold);
            btnClearCart->Click += gcnew EventHandler(this, &StoreForm::btnClearCart_Click);
            this->Controls->Add(btnClearCart);

            Label^ lblFooter = gcnew Label();
            lblFooter->Text = L"💡 Tip: Select a product and click Add to Cart";
            lblFooter->Location = Point(20, 555);
            lblFooter->Size = System::Drawing::Size(940, 25);
            lblFooter->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Italic);
            lblFooter->ForeColor = Color::Gray;
            lblFooter->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(lblFooter);
        }

        void btnLogin_Click(Object^ sender, EventArgs^ e) {
            Form^ loginForm = gcnew Form();
            loginForm->Text = L"Login";
            loginForm->Size = System::Drawing::Size(350, 200);
            loginForm->StartPosition = FormStartPosition::CenterParent;
            loginForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            loginForm->MaximizeBox = false;
            loginForm->BackColor = Color::White;

            Label^ lblName = gcnew Label();
            lblName->Text = L"Enter your name:";
            lblName->Location = Point(20, 30);
            lblName->Size = System::Drawing::Size(300, 25);
            lblName->Font = gcnew System::Drawing::Font(L"Arial", 11);
            loginForm->Controls->Add(lblName);

            TextBox^ txtName = gcnew TextBox();
            txtName->Location = Point(20, 60);
            txtName->Size = System::Drawing::Size(290, 30);
            txtName->Font = gcnew System::Drawing::Font(L"Arial", 12);
            loginForm->Controls->Add(txtName);

            Button^ btnOK = gcnew Button();
            btnOK->Text = L"OK";
            btnOK->Location = Point(20, 110);
            btnOK->Size = System::Drawing::Size(135, 40);
            btnOK->BackColor = Color::FromArgb(76, 175, 80);
            btnOK->ForeColor = Color::White;
            btnOK->FlatStyle = FlatStyle::Flat;
            btnOK->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            loginForm->Controls->Add(btnOK);

            Button^ btnCancel = gcnew Button();
            btnCancel->Text = L"Cancel";
            btnCancel->Location = Point(175, 110);
            btnCancel->Size = System::Drawing::Size(135, 40);
            btnCancel->BackColor = Color::FromArgb(244, 67, 54);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            loginForm->Controls->Add(btnCancel);

            loginForm->AcceptButton = btnOK;
            loginForm->CancelButton = btnCancel;

            if (loginForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                if (!String::IsNullOrWhiteSpace(txtName->Text)) {
                    currentUser = txtName->Text;
                    lblUser->Text = L"👤 " + currentUser;
                    MessageBox::Show(
                        String::Format(L"Welcome {0}! 🎉\nمرحباً {0}!", currentUser),
                        L"Login Success",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }
            }

            delete loginForm;
        }

        void btnAddToCart_Click(Object^ sender, EventArgs^ e) {
            if (listProducts->SelectedIndex < 0) {
                MessageBox::Show(
                    L"Please select a product first!\nالرجاء اختيار منتج أولاً!",
                    L"No Selection",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning
                );
                return;
            }

            Product^ selectedProduct = products[listProducts->SelectedIndex];
            int quantity = (int)numQuantity->Value;

            if (quantity > selectedProduct->Stock) {
                MessageBox::Show(
                    String::Format(L"Not enough stock! Only {0} available.\nالمخزون غير كافٍ! فقط {0} متاح.",
                        selectedProduct->Stock),
                    L"Insufficient Stock",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
                return;
            }

            bool found = false;
            for each (CartItem ^ item in cart) {
                if (item->ProductInfo->Id == selectedProduct->Id) {
                    item->Quantity += quantity;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cart->Add(gcnew CartItem(selectedProduct, quantity));
            }

            UpdateCart();

            MessageBox::Show(
                String::Format(L"✓ Added {0} x {1} to cart!\nتمت الإضافة للسلة!",
                    quantity, selectedProduct->Name),
                L"Success",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
        }

        void btnCheckout_Click(Object^ sender, EventArgs^ e) {
            if (cart->Count == 0) {
                MessageBox::Show(
                    L"Your cart is empty!\nسلتك فارغة!",
                    L"Empty Cart",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );
                return;
            }

            double total = CalculateTotal();

            String^ orderSummary = String::Format(
                L"📋 Order Summary\n\n" +
                L"Customer: {0}\n" +
                L"Items: {1}\n" +
                L"Total: ${2:F2}\n\n" +
                L"Confirm purchase?",
                currentUser,
                cart->Count,
                total
            );

            auto result = MessageBox::Show(
                orderSummary,
                L"Checkout",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                for each (CartItem ^ item in cart) {
                    item->ProductInfo->Stock -= item->Quantity;
                }

                MessageBox::Show(
                    String::Format(
                        L"✅ Order completed successfully!\n" +
                        L"Total: ${0:F2}\n" +
                        L"Thank you for shopping!\n\n" +
                        L"تم الطلب بنجاح!\n" +
                        L"شكراً لتسوقك معنا!",
                        total
                    ),
                    L"Success",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );

                cart->Clear();
                UpdateCart();
                LoadProducts();
            }
        }

        void btnClearCart_Click(Object^ sender, EventArgs^ e) {
            if (cart->Count == 0) return;

            auto result = MessageBox::Show(
                L"Are you sure you want to clear the cart?\nهل تريد تفريغ السلة؟",
                L"Confirm",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                cart->Clear();
                UpdateCart();
                MessageBox::Show(
                    L"Cart cleared!\nتم تفريغ السلة!",
                    L"Success",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );
            }
        }

        void LoadProducts() {
            listProducts->Items->Clear();
            for each (Product ^ p in products) {
                listProducts->Items->Add(p->ToString());
            }
        }

        void UpdateCart() {
            listCart->Items->Clear();
            for each (CartItem ^ item in cart) {
                listCart->Items->Add(item->ToString());
            }

            double total = CalculateTotal();
            lblTotal->Text = String::Format(L"💰 Total: ${0:F2}", total);
        }

        double CalculateTotal() {
            double total = 0;
            for each (CartItem ^ item in cart) {
                total += item->GetTotal();
            }
            return total;
        }
    };
}
