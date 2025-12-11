#pragma once
#include "Models.h"
#include "AdminPanel.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace SimpleStore {

    public ref class StoreForm : public Form {
    private:
        List<Product^>^ products;
        List<CartItem^>^ cart;
        List<User^>^ users;
        String^ currentUser;
        bool isAdmin;

        Panel^ panelTop;
        Label^ lblTitle;
        Label^ lblUser;
        Button^ btnLogin;
        Button^ btnRegister;
        Button^ btnAdminPanel;
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
            users = gcnew List<User^>();
            currentUser = "Guest";
            isAdmin = false;

            // Initialize default users
            users->Add(gcnew User("admin", "admin123", true));
            users->Add(gcnew User("user", "user123", false));

            // Initialize products
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
            this->Size = System::Drawing::Size(1000, 620);
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
            lblUser->Location = Point(550, 25);
            lblUser->Size = System::Drawing::Size(150, 30);
            panelTop->Controls->Add(lblUser);

            btnAdminPanel = gcnew Button();
            btnAdminPanel->Text = L"🔧 Admin";
            btnAdminPanel->Location = Point(710, 20);
            btnAdminPanel->Size = System::Drawing::Size(85, 40);
            btnAdminPanel->BackColor = Color::FromArgb(156, 39, 176);
            btnAdminPanel->ForeColor = Color::White;
            btnAdminPanel->FlatStyle = FlatStyle::Flat;
            btnAdminPanel->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
            btnAdminPanel->Click += gcnew EventHandler(this, &StoreForm::btnAdminPanel_Click);
            btnAdminPanel->Visible = false;
            panelTop->Controls->Add(btnAdminPanel);

            btnRegister = gcnew Button();
            btnRegister->Text = L"📝 Register";
            btnRegister->Location = Point(805, 20);
            btnRegister->Size = System::Drawing::Size(85, 40);
            btnRegister->BackColor = Color::FromArgb(255, 152, 0);
            btnRegister->ForeColor = Color::White;
            btnRegister->FlatStyle = FlatStyle::Flat;
            btnRegister->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            btnRegister->Click += gcnew EventHandler(this, &StoreForm::btnRegister_Click);
            panelTop->Controls->Add(btnRegister);

            btnLogin = gcnew Button();
            btnLogin->Text = L"Login";
            btnLogin->Location = Point(900, 20);
            btnLogin->Size = System::Drawing::Size(70, 40);
            btnLogin->BackColor = Color::FromArgb(76, 175, 80);
            btnLogin->ForeColor = Color::White;
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->Font = gcnew System::Drawing::Font(L"Arial", 10, FontStyle::Bold);
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
        }

        void btnRegister_Click(Object^ sender, EventArgs^ e) {
            Form^ registerForm = gcnew Form();
            registerForm->Text = L"📝 Register New Account - إنشاء حساب جديد";
            registerForm->Size = System::Drawing::Size(400, 350);
            registerForm->StartPosition = FormStartPosition::CenterParent;
            registerForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            registerForm->MaximizeBox = false;
            registerForm->BackColor = Color::White;

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = L"Create New Account";
            lblTitle->Location = Point(20, 20);
            lblTitle->Size = System::Drawing::Size(350, 30);
            lblTitle->Font = gcnew System::Drawing::Font(L"Arial", 14, FontStyle::Bold);
            lblTitle->ForeColor = Color::FromArgb(255, 152, 0);
            registerForm->Controls->Add(lblTitle);

            Label^ lblUsername = gcnew Label();
            lblUsername->Text = L"Username - اسم المستخدم:";
            lblUsername->Location = Point(20, 65);
            lblUsername->Size = System::Drawing::Size(350, 25);
            lblUsername->Font = gcnew System::Drawing::Font(L"Arial", 11);
            registerForm->Controls->Add(lblUsername);

            TextBox^ txtUsername = gcnew TextBox();
            txtUsername->Location = Point(20, 95);
            txtUsername->Size = System::Drawing::Size(340, 30);
            txtUsername->Font = gcnew System::Drawing::Font(L"Arial", 12);
            registerForm->Controls->Add(txtUsername);

            Label^ lblPassword = gcnew Label();
            lblPassword->Text = L"Password - كلمة المرور:";
            lblPassword->Location = Point(20, 140);
            lblPassword->Size = System::Drawing::Size(350, 25);
            lblPassword->Font = gcnew System::Drawing::Font(L"Arial", 11);
            registerForm->Controls->Add(lblPassword);

            TextBox^ txtPassword = gcnew TextBox();
            txtPassword->Location = Point(20, 170);
            txtPassword->Size = System::Drawing::Size(340, 30);
            txtPassword->Font = gcnew System::Drawing::Font(L"Arial", 12);
            txtPassword->PasswordChar = '●';
            registerForm->Controls->Add(txtPassword);

            Label^ lblConfirm = gcnew Label();
            lblConfirm->Text = L"Confirm Password - تأكيد كلمة المرور:";
            lblConfirm->Location = Point(20, 215);
            lblConfirm->Size = System::Drawing::Size(350, 25);
            lblConfirm->Font = gcnew System::Drawing::Font(L"Arial", 11);
            registerForm->Controls->Add(lblConfirm);

            TextBox^ txtConfirm = gcnew TextBox();
            txtConfirm->Location = Point(20, 245);
            txtConfirm->Size = System::Drawing::Size(340, 30);
            txtConfirm->Font = gcnew System::Drawing::Font(L"Arial", 12);
            txtConfirm->PasswordChar = '●';
            registerForm->Controls->Add(txtConfirm);

            Button^ btnCreate = gcnew Button();
            btnCreate->Text = L"✓ Create Account";
            btnCreate->Location = Point(20, 290);
            btnCreate->Size = System::Drawing::Size(160, 40);
            btnCreate->BackColor = Color::FromArgb(76, 175, 80);
            btnCreate->ForeColor = Color::White;
            btnCreate->FlatStyle = FlatStyle::Flat;
            btnCreate->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnCreate->DialogResult = System::Windows::Forms::DialogResult::OK;
            registerForm->Controls->Add(btnCreate);

            Button^ btnCancel = gcnew Button();
            btnCancel->Text = L"✖ Cancel";
            btnCancel->Location = Point(200, 290);
            btnCancel->Size = System::Drawing::Size(160, 40);
            btnCancel->BackColor = Color::FromArgb(244, 67, 54);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            registerForm->Controls->Add(btnCancel);

            registerForm->AcceptButton = btnCreate;
            registerForm->CancelButton = btnCancel;

            if (registerForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                String^ username = txtUsername->Text->Trim();
                String^ password = txtPassword->Text;
                String^ confirm = txtConfirm->Text;

                // Validation
                if (String::IsNullOrWhiteSpace(username)) {
                    MessageBox::Show(
                        L"Please enter a username!\nالرجاء إدخال اسم المستخدم!",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                if (username->Length < 3) {
                    MessageBox::Show(
                        L"Username must be at least 3 characters!\nاسم المستخدم يجب أن يكون 3 أحرف على الأقل!",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                if (String::IsNullOrWhiteSpace(password)) {
                    MessageBox::Show(
                        L"Please enter a password!\nالرجاء إدخال كلمة المرور!",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                if (password->Length < 4) {
                    MessageBox::Show(
                        L"Password must be at least 4 characters!\nكلمة المرور يجب أن تكون 4 أحرف على الأقل!",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                if (password != confirm) {
                    MessageBox::Show(
                        L"Passwords do not match!\nكلمات المرور غير متطابقة!",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                // Check if username already exists
                bool userExists = false;
                for each (User ^ user in users) {
                    if (user->Username->ToLower() == username->ToLower()) {
                        userExists = true;
                        break;
                    }
                }

                if (userExists) {
                    MessageBox::Show(
                        L"Username already exists! Please choose another.\nاسم المستخدم موجود مسبقاً! الرجاء اختيار اسم آخر.",
                        L"Error",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                    return;
                }

                // Create new user
                users->Add(gcnew User(username, password, false));

                MessageBox::Show(
                    String::Format(L"✅ Account created successfully!\n\nUsername: {0}\n\nYou can now login with your credentials.\n\nتم إنشاء الحساب بنجاح!\nيمكنك الآن تسجيل الدخول.", username),
                    L"Success",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );
            }
        }

        void btnLogin_Click(Object^ sender, EventArgs^ e) {
            if (btnLogin->Text == L"Logout") {
                // Logout
                auto result = MessageBox::Show(
                    L"Are you sure you want to logout?\nهل تريد تسجيل الخروج؟",
                    L"Confirm Logout",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    currentUser = "Guest";
                    isAdmin = false;
                    lblUser->Text = L"👤 Guest";
                    btnAdminPanel->Visible = false;
                    btnLogin->Text = L"Login";
                    btnRegister->Visible = true;

                    MessageBox::Show(
                        L"Logged out successfully!\nتم تسجيل الخروج بنجاح!",
                        L"Logout",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }
                return;
            }

            Form^ loginForm = gcnew Form();
            loginForm->Text = L"🔐 Login - تسجيل الدخول";
            loginForm->Size = System::Drawing::Size(350, 270);
            loginForm->StartPosition = FormStartPosition::CenterParent;
            loginForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            loginForm->MaximizeBox = false;
            loginForm->BackColor = Color::White;

            Label^ lblUsername = gcnew Label();
            lblUsername->Text = L"Username - اسم المستخدم:";
            lblUsername->Location = Point(20, 30);
            lblUsername->Size = System::Drawing::Size(300, 25);
            lblUsername->Font = gcnew System::Drawing::Font(L"Arial", 11);
            loginForm->Controls->Add(lblUsername);

            TextBox^ txtUsername = gcnew TextBox();
            txtUsername->Location = Point(20, 60);
            txtUsername->Size = System::Drawing::Size(290, 30);
            txtUsername->Font = gcnew System::Drawing::Font(L"Arial", 12);
            loginForm->Controls->Add(txtUsername);

            Label^ lblPassword = gcnew Label();
            lblPassword->Text = L"Password - كلمة المرور:";
            lblPassword->Location = Point(20, 100);
            lblPassword->Size = System::Drawing::Size(300, 25);
            lblPassword->Font = gcnew System::Drawing::Font(L"Arial", 11);
            loginForm->Controls->Add(lblPassword);

            TextBox^ txtPassword = gcnew TextBox();
            txtPassword->Location = Point(20, 130);
            txtPassword->Size = System::Drawing::Size(290, 30);
            txtPassword->Font = gcnew System::Drawing::Font(L"Arial", 12);
            txtPassword->PasswordChar = '●';
            loginForm->Controls->Add(txtPassword);

            Button^ btnOK = gcnew Button();
            btnOK->Text = L"✓ Login";
            btnOK->Location = Point(20, 180);
            btnOK->Size = System::Drawing::Size(135, 40);
            btnOK->BackColor = Color::FromArgb(76, 175, 80);
            btnOK->ForeColor = Color::White;
            btnOK->FlatStyle = FlatStyle::Flat;
            btnOK->Font = gcnew System::Drawing::Font(L"Arial", 11, FontStyle::Bold);
            btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
            loginForm->Controls->Add(btnOK);

            Button^ btnCancel = gcnew Button();
            btnCancel->Text = L"✖ Cancel";
            btnCancel->Location = Point(175, 180);
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
                String^ username = txtUsername->Text;
                String^ password = txtPassword->Text;

                bool loginSuccess = false;
                for each (User ^ user in users) {
                    if (user->Username == username && user->Password == password) {
                        currentUser = username;
                        isAdmin = user->IsAdmin;
                        loginSuccess = true;
                        break;
                    }
                }

                if (loginSuccess) {
                    lblUser->Text = L"👤 " + currentUser + (isAdmin ? L" (Admin)" : L"");
                    btnAdminPanel->Visible = isAdmin;
                    btnLogin->Text = L"Logout";
                    btnRegister->Visible = false;

                    MessageBox::Show(
                        String::Format(L"Welcome {0}! 🎉\nمرحباً {0}!\n\n{1}",
                            currentUser,
                            isAdmin ? L"Admin access granted" : L""),
                        L"Login Success",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Information
                    );
                }
                else {
                    MessageBox::Show(
                        L"Invalid username or password!\nاسم مستخدم أو كلمة مرور خاطئة!",
                        L"Login Failed",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Error
                    );
                }
            }
        }

        void btnAdminPanel_Click(Object^ sender, EventArgs^ e) {
            if (!isAdmin) return;

            AdminPanel^ adminPanel = gcnew AdminPanel(products);
            adminPanel->ShowDialog();
            LoadProducts();
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
