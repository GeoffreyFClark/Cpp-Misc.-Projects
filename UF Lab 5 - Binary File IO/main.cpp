#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Weapon {
    string name;
    int powerRating;
    float powerConsumption;
};

struct Starship {
    string name;
    string shipClass;
    short length;
    int shieldCapacity;
    float warpSpeed;
    vector<Weapon> weapons;
    int totalFirepower = 0;
};

string readString(ifstream& file) {
    int length;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    char* buffer = new char[length];
    file.read(buffer, length);
    string str(buffer);
    delete[] buffer;
    return str;
}

Weapon readWeapon(ifstream& file) {
    Weapon weapon;
    weapon.name = readString(file);
    file.read(reinterpret_cast<char*>(&weapon.powerRating), sizeof(weapon.powerRating));
    file.read(reinterpret_cast<char*>(&weapon.powerConsumption), sizeof(weapon.powerConsumption));
    return weapon;
}

Starship readStarship(ifstream& file) {
    Starship starship;
    starship.name = readString(file);
    starship.shipClass = readString(file);
    file.read(reinterpret_cast<char*>(&starship.length), sizeof(starship.length));
    file.read(reinterpret_cast<char*>(&starship.shieldCapacity), sizeof(starship.shieldCapacity));
    file.read(reinterpret_cast<char*>(&starship.warpSpeed), sizeof(starship.warpSpeed));
    int numWeapons;
    file.read(reinterpret_cast<char*>(&numWeapons), sizeof(numWeapons));
    for (int i = 0; i < numWeapons; i++) {
        Weapon weapon = readWeapon(file);
        starship.weapons.push_back(weapon);
        starship.totalFirepower += weapon.powerRating;
    }
    return starship;
}

vector<Starship> loadStarships(const string& filename) {
    vector<Starship> starships;
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return starships;
    }

    int numStarships;
    file.read(reinterpret_cast<char*>(&numStarships), sizeof(numStarships));
    for (int i = 0; i < numStarships; i++) {
        Starship starship = readStarship(file);
        starships.push_back(starship);
    }

    file.close();
    return starships;
}

void printAllStarships(const vector<Starship>& starships) {
    for (const Starship& starship : starships) {
        cout << "Name: " << starship.name << endl;
        cout << "Class: " << starship.shipClass << endl;
        cout << "Length: " << starship.length << endl;
        cout << "Shield capacity: " << starship.shieldCapacity << endl;
        cout << "Maximum Warp: " << starship.warpSpeed << endl;
        cout << "Armaments:" << endl;
            if (starship.weapons.empty()) {
                cout << "Unarmed" << endl;
            } else {
                for (const Weapon& weapon : starship.weapons) {
                    cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
                }
            }
        if (starship.totalFirepower > 0) {
            cout << "Total firepower: " << starship.totalFirepower << endl;
        }
        cout << endl;
    }
}

Starship findStarshipWithStrongestWeapon(const vector<Starship>& starships) {
    Starship strongestStarship;
    int maxPowerRating = 0;

    for (const Starship& starship : starships) {
        for (const Weapon& weapon : starship.weapons) {
            if (weapon.powerRating > maxPowerRating) {
                maxPowerRating = weapon.powerRating;
                strongestStarship = starship;
            }
        }
    }

    return strongestStarship;
}

Starship findMostPowerfulStarship(const vector<Starship>& starships) {
    Starship mostPowerfulStarship;
    int maxCombinedPowerRating = 0;

    for (const Starship& starship : starships) {
        int combinedPowerRating = 0;
        for (const Weapon& weapon : starship.weapons) {
            combinedPowerRating += weapon.powerRating;
        }
        if (combinedPowerRating > maxCombinedPowerRating) {
            maxCombinedPowerRating = combinedPowerRating;
            mostPowerfulStarship = starship;
        }
    }

    return mostPowerfulStarship;
}

Starship findWeakestShip(const vector<Starship>& starships) {
    Starship weakestShip;
    int minPowerRating = 2147483647;
    int minWeaponPowerRating = 2147483647;

    for (const Starship& starship : starships) {
        if (!starship.weapons.empty()) {
            for (const Weapon& weapon : starship.weapons) {
                if (weapon.powerRating < minWeaponPowerRating) {
                    minWeaponPowerRating = weapon.powerRating;
                }
            }
            if (minWeaponPowerRating < minPowerRating) {
                minPowerRating = minWeaponPowerRating;
                weakestShip = starship;
            }
        }
    }

    return weakestShip;
}

void printUnarmedShips(const vector<Starship>& starships) {
    for (const Starship& starship : starships) {
        if (starship.weapons.empty()) {
            cout << "Name: " << starship.name << endl;
            cout << "Class: " << starship.shipClass << endl;
            cout << "Length: " << starship.length << endl;
            cout << "Shield capacity: " << starship.shieldCapacity << endl;
            cout << "Maximum Warp: " << starship.warpSpeed << endl;
            cout << "Armaments: Unarmed" << endl;
            cout << endl;
        }
    }
}

int main() {
    // cout << "Which file(s) to open?\n";
    // cout << "1. friendlyships.shp" << endl;
    // cout << "2. enemyships.shp" << endl;
    // cout << "3. Both files" << endl;
    int option;
    cin >> option;

    vector<Starship> starships;
    if (option == 1) {
        starships = loadStarships("friendlyships.shp");
    } else if (option == 2) {
        starships = loadStarships("enemyships.shp");
    } else if (option == 3) {
        vector<Starship> friendlyships = loadStarships("friendlyships.shp");
        vector<Starship> enemyships = loadStarships("enemyships.shp");
        starships.insert(starships.end(), friendlyships.begin(), friendlyships.end());
        starships.insert(starships.end(), enemyships.begin(), enemyships.end());
    }

    // cout << "1. Print all ships" << endl;
    // cout << "2. Starship with the strongest weapon" << endl;
    // cout << "3. Strongest starship overall" << endl;
    // cout << "4. Weakest ship (ignoring unarmed)" << endl;
    // cout << "5. Unarmed ships" << endl;

    cin >> option;

    switch (option) {
        case 1:
            printAllStarships(starships);
            break;
        case 2: {
            Starship strongestWeaponStarship = findStarshipWithStrongestWeapon(starships);
            if (!strongestWeaponStarship.name.empty()) {
                cout << "Name: " << strongestWeaponStarship.name << endl;
                cout << "Class: " << strongestWeaponStarship.shipClass << endl;
                cout << "Length: " << strongestWeaponStarship.length << endl;
                cout << "Shield capacity: " << strongestWeaponStarship.shieldCapacity << endl;
                cout << "Maximum Warp: " << strongestWeaponStarship.warpSpeed << endl;
                cout << "Armaments:" << endl;
                    if (strongestWeaponStarship.weapons.empty()) {
                        cout << "Unarmed" << endl;
                    } else {
                        for (const Weapon& weapon : strongestWeaponStarship.weapons) {
                            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
                        }
                    }
                cout << "Total firepower: " << strongestWeaponStarship.totalFirepower << endl;
                cout << endl;
            } else {
                cout << "No starship with weapons found." << endl;
            }
            break;
        }
        case 3: {
            Starship mostPowerfulStarship = findMostPowerfulStarship(starships);
            if (!mostPowerfulStarship.name.empty()) {
                cout << "Name: " << mostPowerfulStarship.name << endl;
                cout << "Class: " << mostPowerfulStarship.shipClass << endl;
                cout << "Length: " << mostPowerfulStarship.length << endl;
                cout << "Shield capacity: " << mostPowerfulStarship.shieldCapacity << endl;
                cout << "Maximum Warp: " << mostPowerfulStarship.warpSpeed << endl;
                cout << "Armaments:" << endl;
                    if (mostPowerfulStarship.weapons.empty()) {
                        cout << "Unarmed" << endl;
                    } else {
                        for (const Weapon& weapon : mostPowerfulStarship.weapons) {
                            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
                        }
                    }
                cout << "Total firepower: " << mostPowerfulStarship.totalFirepower << endl;
                cout << endl;
            } else {
                cout << "No starship with weapons found." << endl;
            }
            break;
        }
        case 4: {
            Starship weakestShip = findWeakestShip(starships);
            if (!weakestShip.name.empty()) {
                cout << "Name: " << weakestShip.name << endl;
                cout << "Class: " << weakestShip.shipClass << endl;
                cout << "Length: " << weakestShip.length << endl;
                cout << "Shield capacity: " << weakestShip.shieldCapacity << endl;
                cout << "Maximum Warp: " << weakestShip.warpSpeed << endl;
                cout << "Armaments:" << endl;
                    if (weakestShip.weapons.empty()) {
                        cout << "Unarmed" << endl;
                    } else {
                        for (const Weapon& weapon : weakestShip.weapons) {
                            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
                        }
                    }
                cout << "Total firepower: " << weakestShip.totalFirepower << endl;
                cout << endl;
            } else {
                cout << "No starship with weapons found." << endl;
            }
            break;
        }
        case 5:
            printUnarmedShips(starships);
            break;
        default:
            cout << "Invalid option." << endl;
            break;
    }

    return 0;
}
