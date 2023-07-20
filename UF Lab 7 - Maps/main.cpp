#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <random>
#include <ctime>

using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

struct StateData {
    string state;
    int perCapitaIncome;
    int population;
    int medianHouseholdIncome;
    int numberOfHouseholds;
};

void RollDice(int numberOfRolls, int numberOfSides)
{
    map<int, int> diceRolls;
    
    for (int i = 1; i <= numberOfSides; i++) {
        diceRolls[i] = 0;
    }
    
    for (int i = 0; i < numberOfRolls; i++) {
        int roll = Random(1, numberOfSides);
        diceRolls[roll]++;
    }
    
    for (const auto& roll : diceRolls) {
        cout << roll.first << ": " << roll.second <<endl;
    }
}

int main()
{
    cout << "1. Random Numbers" << endl;
    cout << "2. State Info" << endl;

    int option;
    cin >> option;

    if (option == 1)
    {
        int randomSeed;
        cout << "Random seed value: " << endl;
        cin >> randomSeed;
        random_mt.seed(randomSeed);

        int numberOfRolls;
        cout << "Number of times to roll the die: " << endl;
        cin >> numberOfRolls;

        int numberOfSides;
        cout << "Number of sides on this die: " << endl;
        cin >> numberOfSides;

        RollDice(numberOfRolls, numberOfSides);
    }
    else if (option == 2)
    {
        ifstream file("states.csv");
        if (!file) {
            cerr << "Error opening file." << endl;
            return 1;
        }
        
        map<string, StateData> states;
        
        string line;
        getline(file, line); // Skip header line
        
        while (getline(file, line)) {
            stringstream ss(line);
            string state, perCapitaIncomeStr, populationStr, medianHouseholdIncomeStr, numberOfHouseholdsStr;
            
            getline(ss, state, ',');
            getline(ss, perCapitaIncomeStr, ',');
            getline(ss, populationStr, ',');
            getline(ss, medianHouseholdIncomeStr, ',');
            getline(ss, numberOfHouseholdsStr, ',');
            
            StateData stateData;
            stateData.state = state;
            stateData.perCapitaIncome = stoi(perCapitaIncomeStr);
            stateData.population = stoi(populationStr);
            stateData.medianHouseholdIncome = stoi(medianHouseholdIncomeStr);
            stateData.numberOfHouseholds = stoi(numberOfHouseholdsStr);
            
            states[state] = stateData;
        }
        
        int stateOption;
        cout << "1. Print all states" << endl;
        cout << "2. Search for a state" << endl;
        cin >> stateOption;
        
        if (stateOption == 1) {
            for (const auto& state : states) {
                cout << state.first << endl;
                cout << "Population: " << state.second.population << endl;
                cout << "Per Capita Income: " << state.second.perCapitaIncome << endl;
                cout << "Median Household Income: " << state.second.medianHouseholdIncome << endl;
                cout << "Number of Households: " << state.second.numberOfHouseholds << endl;
                cout << endl;
            }
        } else if (stateOption == 2) {
            string searchState;
            cin >> searchState;
            
            auto it = states.find(searchState);
            if (it != states.end()) {
                cout << it->first << endl;
                cout << "Population: " << it->second.population << endl;
                cout << "Per Capita Income: " << it->second.perCapitaIncome << endl;
                cout << "Median Household Income: " << it->second.medianHouseholdIncome << endl;
                cout << "Number of Households: " << it->second.numberOfHouseholds << endl;
            } else {
                cout << "No match found for " << searchState << endl;
            }
        }
    }

    return 0;
}
