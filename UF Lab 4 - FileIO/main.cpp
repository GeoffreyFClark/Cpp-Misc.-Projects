#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct LegoSet {
    string number;
    string theme;
    string name;
    int minifigs;
    int pieces;
    double price;
};

vector<LegoSet> loadSetsFromFile(const string& filename) {
    vector<LegoSet> sets;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
    }
    string line;
    getline(file, line); // Skip the header line
    while (getline(file, line)) {
        stringstream strstream1(line);
        string number, theme, name, minifigs, pieces, price;
        getline(strstream1, number, ',');
        getline(strstream1, theme, ',');
        getline(strstream1, name, ',');
        getline(strstream1, minifigs, ',');
        getline(strstream1, pieces, ',');
        getline(strstream1, price, ',');
        LegoSet set;
        set.number = number;
        set.theme = theme;
        set.name = name;
        set.minifigs = stoi(minifigs);
        set.pieces = stoi(pieces);
        set.price = stod(price);
        sets.push_back(set);
    }
    file.close();
    return sets;
}

LegoSet findMostExpensiveSet(const vector<LegoSet>& sets) {
    LegoSet maxPriceSet = sets[0];
    for (const LegoSet& set : sets) {
        if (set.price > maxPriceSet.price) {
            maxPriceSet = set;
        }
    }
    return maxPriceSet;
}

LegoSet findLeastExpensiveSet(const vector<LegoSet>& sets) {
    LegoSet minPriceSet = sets[0];
    for (const LegoSet& set : sets) {
        if (set.price < minPriceSet.price) {
            minPriceSet = set;
        }
    }
    return minPriceSet;
}

LegoSet findSetWithLargestPieceCount(const vector<LegoSet>& sets) {
    LegoSet maxPiecesSet = sets[0];
    for (const LegoSet& set : sets) {
        if (set.pieces > maxPiecesSet.pieces) {
            maxPiecesSet = set;
        }
    }
    return maxPiecesSet;
}

vector<LegoSet> searchSetsByName(const vector<LegoSet>& sets, const string& searchTerm) {
    vector<LegoSet> matchingSets;
    for (const auto& set : sets) {
        if (set.name.find(searchTerm) != string::npos) {
            matchingSets.push_back(set);
        }
    }
    return matchingSets;
}

vector<LegoSet> searchSetsByTheme(const vector<LegoSet>& sets, const string& searchTerm) {
    vector<LegoSet> matchingSets;
    for (const auto& set : sets) {
        if (set.theme.find(searchTerm) != string::npos) {
            matchingSets.push_back(set);
        }
    }
    return matchingSets;
}

int calculateAverageMiniFigCount(const vector<LegoSet>& sets) {
    int totalMiniFigs = 0;
    for (const auto& set : sets) {
        totalMiniFigs += set.minifigs;
    }
    return totalMiniFigs / sets.size();
}


double calculateAveragePrice(const vector<LegoSet>& sets) {
    double totalPrice = 0;
    for (const auto& set : sets) {
        totalPrice += set.price;
    }
    return totalPrice / sets.size();
}

LegoSet findSetWithMostMinifigures(const vector<LegoSet>& sets) {
    LegoSet maxMinifigsSet = sets[0];
    for (const LegoSet& set : sets) {
        if (set.minifigs > maxMinifigsSet.minifigs) {
            maxMinifigsSet = set;
        }
    }
    return maxMinifigsSet;
}

tuple<double, int, int> calculateTotalCostAndPieces(const vector<LegoSet>& sets) {
    double totalCost = 0;
    int totalPieces = 0;
    int totalMinifigs = 0;
    for (const auto& set : sets) {
        totalCost += set.price;
        totalPieces += set.pieces;
        totalMinifigs += set.minifigs;
    }
    return make_tuple(totalCost, totalPieces, totalMinifigs);
}

int main() {
    cout << fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;
    string option;
    cin >> option;
    cin.ignore();

    vector<LegoSet> setsFromFile;

    if (option == "1") {
        setsFromFile = loadSetsFromFile("lego1.csv");
    } else if (option == "2") {
        setsFromFile = loadSetsFromFile("lego2.csv");
    } else if (option == "3") {
        setsFromFile = loadSetsFromFile("lego3.csv");
    } else if (option == "4") {
        vector<LegoSet> sets1 = loadSetsFromFile("lego1.csv");
        vector<LegoSet> sets2 = loadSetsFromFile("lego2.csv");
        vector<LegoSet> sets3 = loadSetsFromFile("lego3.csv");
        setsFromFile.insert(setsFromFile.end(), sets1.begin(), sets1.end());
        setsFromFile.insert(setsFromFile.end(), sets2.begin(), sets2.end());
        setsFromFile.insert(setsFromFile.end(), sets3.begin(), sets3.end());
    } else {
        cout << "Invalid option. Exiting..." << endl;
    }

    if (setsFromFile.empty()) {
        cout << "No LEGO sets loaded. Exiting..." << endl;
    }

    cout << "1. Most Expensive set" << endl;
    cout << "2. Largest piece count" << endl;
    cout << "3. Search for set name containing..." << endl;
    cout << "4. Search themes..." << endl;
    cout << "5. Part count information" << endl;
    cout << "6. Price information" << endl;
    cout << "7. Minifigure information" << endl;
    cout << "8. If you bought one of everything..." << endl;
    cout << "0. Exit" << endl;

    string choice;
    cin >> choice;

    if (choice == "1") {
        LegoSet mostExpensiveSet = findMostExpensiveSet(setsFromFile);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        cout << "The most expensive set is:" << endl;
        cout << "Name: " << mostExpensiveSet.name << endl;
        cout << "Number: " << mostExpensiveSet.number << endl;
        cout << "Theme: " << mostExpensiveSet.theme << endl;
        cout << "Price: $" << mostExpensiveSet.price << endl;
        cout << "Minifigures: " << mostExpensiveSet.minifigs << endl;
        cout << "Piece count: " << mostExpensiveSet.pieces << endl;
    } else if (choice == "2") {
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        LegoSet setWithLargestPieceCount = findSetWithLargestPieceCount(setsFromFile);
        cout << "The set with the highest parts count:" << endl;
        cout << "Name: " << setWithLargestPieceCount.name << endl;
        cout << "Number: " << setWithLargestPieceCount.number << endl;
        cout << "Theme: " << setWithLargestPieceCount.theme << endl;
        cout << "Price: $" << setWithLargestPieceCount.price << endl;
        cout << "Minifigures: " << setWithLargestPieceCount.minifigs << endl;
        cout << "Piece count: " << setWithLargestPieceCount.pieces << endl;
    } else if (choice == "3") {
        // cout << "Enter the search term for set name: ";
        string searchTerm;
        cin.ignore();
        getline(cin, searchTerm);
        vector<LegoSet> matchingSets = searchSetsByName(setsFromFile, searchTerm);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        if (matchingSets.empty()) {
            cout << "No sets found matching that search term" << endl;
        } else {
            cout << "Sets matching \"" << searchTerm << "\":" << endl;
            for (const auto& set : matchingSets) {
                cout << set.number << " " << set.name << " $" << set.price << endl;
            }
        }
    } else if (choice == "4") {
        cout << "Enter the search term for theme: ";
        string searchTerm;
        cin.ignore();
        getline(cin, searchTerm);
        vector<LegoSet> matchingSets = searchSetsByTheme(setsFromFile, searchTerm);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        if (matchingSets.empty()) {
            cout << "No sets found matching that search term" << endl;
        } else {
            cout << "Sets matching \"" << searchTerm << "\":" << endl;
            for (const auto& set : matchingSets) {
                cout << set.number << " " << set.name << " $" << set.price << endl;
            }
        }
    } else if (choice == "5") {
        tuple<double, int, int> costPiecesMiniFigs = calculateTotalCostAndPieces(setsFromFile);
        int averagePartCount = get<1>(costPiecesMiniFigs) / setsFromFile.size();
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        cout << "Average part count for " << setsFromFile.size() << " sets: " << averagePartCount << endl;
    } else if (choice == "6") {
        double averagePrice = calculateAveragePrice(setsFromFile);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        cout << "Average price for " << setsFromFile.size() << " sets: $" << averagePrice << '\n' << endl;

        LegoSet leastExpensiveSet = findLeastExpensiveSet(setsFromFile);
        cout << "Least expensive set:" << endl;
        cout << "Name: " << leastExpensiveSet.name << endl;
        cout << "Number: " << leastExpensiveSet.number << endl;
        cout << "Theme: " << leastExpensiveSet.theme << endl;
        cout << "Price: $" << leastExpensiveSet.price << endl;
        cout << "Minifigures: " << leastExpensiveSet.minifigs << endl;
        cout << "Piece count: " << leastExpensiveSet.pieces << endl;

        LegoSet mostExpensiveSet = findMostExpensiveSet(setsFromFile);
        cout << "Most expensive set:" << endl;
        cout << "Name: " << mostExpensiveSet.name << endl;
        cout << "Number: " << mostExpensiveSet.number << endl;
        cout << "Theme: " << mostExpensiveSet.theme << endl;
        cout << "Price: $" << mostExpensiveSet.price << endl;
        cout << "Minifigures: " << mostExpensiveSet.minifigs << endl;
        cout << "Piece count: " << mostExpensiveSet.pieces << endl;
    } else if (choice == "7") {
        LegoSet setWithMostMinifigures = findSetWithMostMinifigures(setsFromFile);
        int averageMinifigures = calculateAverageMiniFigCount(setsFromFile);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        cout << "Average number of minifigures: " << averageMinifigures << '\n' << endl;
        cout << "Set with the most minifigures:" << endl;
        cout << "Name: " << setWithMostMinifigures.name << endl;
        cout << "Number: " << setWithMostMinifigures.number << endl;
        cout << "Theme: " << setWithMostMinifigures.theme << endl;
        cout << "Price: $" << setWithMostMinifigures.price << endl;
        cout << "Minifigures: " << setWithMostMinifigures.minifigs << endl;
        cout << "Piece count: " << setWithMostMinifigures.pieces << endl;
    } else if (choice == "8") {
        tuple<double, int, int> totalCostAndPieces = calculateTotalCostAndPieces(setsFromFile);
        cout << "Total number of sets: " << setsFromFile.size() << '\n' << endl;
        cout << "If you bought one of everything..." << endl;
        cout << "It would cost: $" << get<0>(totalCostAndPieces) << endl;
        cout << "You would have " << get<1>(totalCostAndPieces) << " pieces in your collection" << endl;
        cout << "You would have an army of " << get<2>(totalCostAndPieces) << " minifigures!" << endl;
    } else if (choice == "0") {
        cout << "Exiting..." << endl;
    } else {
        cout << "Invalid choice. Exiting..." << endl;
}
    return 0;
}
