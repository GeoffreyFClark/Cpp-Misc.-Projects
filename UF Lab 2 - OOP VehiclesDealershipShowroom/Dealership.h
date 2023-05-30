#include "Showroom.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Dealership {
private:
    string _name;
    int _capacity;
    vector<Showroom> _showrooms;
    
public:
    Dealership(string name = "Generic Dealership",
               unsigned int capacity = 0);
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();
};
    
