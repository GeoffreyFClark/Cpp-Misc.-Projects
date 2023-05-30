#pragma once

#include <vector>
#include <string>
#include "Vehicle.h"
#include <iostream>
using namespace std;

class Showroom {
private:
    string _name;
    vector<Vehicle> _vehicles;
    int _capacity;
    
public:
    Showroom(string name = "Unnamed Showroom", unsigned int capacity = 0);
    vector<Vehicle> GetVehicleList();
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};
