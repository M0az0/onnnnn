#pragma once
using namespace System;

public ref class Product {
public:
    int Id;
    String^ Name;
    double Price;
    int Stock;

    Product(int id, String^ name, double price, int stock) {
        Id = id;
        Name = name;
        Price = price;
        Stock = stock;
    }

    virtual String^ ToString() override {
        return String::Format("{0} - ${1:F2} (Stock: {2})", Name, Price, Stock);
    }
};

public ref class CartItem {
public:
    Product^ ProductInfo;
    int Quantity;

    CartItem(Product^ product, int qty) {
        ProductInfo = product;
        Quantity = qty;
    }

    double GetTotal() {
        return ProductInfo->Price * Quantity;
    }

    virtual String^ ToString() override {
        return String::Format("{0} x {1} = ${2:F2}",
            Quantity, ProductInfo->Name, GetTotal());
    }
};
