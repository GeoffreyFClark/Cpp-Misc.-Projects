#include "Showroom.h"

Showroom::Showroom(string name, unsigned int capacity){
    _name = name;
    _capacity = capacity;
};

vector<Vehicle> Showroom::GetVehicleList(){
    return _vehicles;
};

void Showroom::AddVehicle(Vehicle v){
    if (_vehicles.size() >= _capacity){
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    }
    else {
        _vehicles.push_back(v);
    };
};

void Showroom::ShowInventory(){
    
    if (_capacity != 0){
        cout << "Vehicles in " + _name << endl;
        for (int i = 0; i < _vehicles.size(); i++){
            _vehicles[i].Display();
        }
    } else { cout << _name << " is empty!" << endl;}
};

float Showroom::GetInventoryValue(){
    int sum = 0;
    for (int i = 0; i < _vehicles.size(); i++){
        sum += _vehicles[i].GetPrice();
    }
    return sum;
};

