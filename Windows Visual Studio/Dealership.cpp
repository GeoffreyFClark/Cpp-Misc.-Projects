#include "Dealership.h"

Dealership::Dealership(string name, unsigned int capacity){
    _name = name;
    _capacity = capacity;
};

void Dealership::AddShowroom(Showroom s){
    if (_showrooms.size() >= _capacity) {
        cout << "Dealership is full, can't add another showroom!" << endl;}
    else {
        _showrooms.push_back(s);
    };
    
};

float Dealership::GetAveragePrice(){
    if (_showrooms.size() == 0) {
        return 0.00;
    } else {
        float sum = 0.00;
        int numcars = 0;
        for (int i = 0; i < _showrooms.size(); i++){
            sum += _showrooms[i].GetInventoryValue();
            numcars += _showrooms[i].GetVehicleList().size();
        };
        float average = sum / numcars;
        return average;
    };
};

void Dealership::ShowInventory(){
    
    if (_showrooms.size() == 0) {
        cout << "Generic Dealership is empty!" << endl;
        cout << "Average car price: $0.00";
    } else {
        for (int i = 0; i < _showrooms.size(); i++){
            _showrooms[i].ShowInventory();
            cout << endl;
        };
        cout << "Average car price: $" << GetAveragePrice();
    };
};

    
