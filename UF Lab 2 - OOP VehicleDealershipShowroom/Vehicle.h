#pragma once

#include <string>
using namespace std;

class Vehicle {
private:
    string _make;
    string _model;
    int _year;
    float _price;
    int _mileage;
    
public:
    Vehicle(string make = "COP3503",
            string model = "Rust Bucket",
            int year = 1900,
            float price = 0,
            int mileage = 0);
    void Display();
    string GetYearMakeModel();
    float GetPrice();
};
