#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle(string make, string model, int year, float price, int mileage){
    _make = make;
    _model = model;
    _year = year;
    _price = price;
    _mileage = mileage;

};

void Vehicle::Display(){
cout << _year << " " << _make << " " << _model << " $" << _price << " " << _mileage << endl;

};

string Vehicle::GetYearMakeModel(){
    string yearmakemodel = to_string(_year) + " " + _make + " " + _model;
    return yearmakemodel;
};

float Vehicle::GetPrice(){
    return _price;
};
