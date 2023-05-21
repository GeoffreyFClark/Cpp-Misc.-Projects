#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    string datatitle;
    string column1;
    string column2;
    string datapoint; 
    vector<string> column1datatable;
    vector<int> column2datatable;

    //Get some input for the title
    cout << "Enter a title for the data:\n"; 
    getline(cin, datatitle);
    cout << "You entered: " << datatitle << "\n";

    //Get some input for column header #1
    cout << "Enter the column 1 header:\n";
    getline(cin, column1);
    cout << "You entered: " << column1 << "\n";

    //Get some input for column header #2
    cout << "Enter the column 2 header:\n";
    getline(cin, column2);
    cout << "You entered: " << column2 << endl;

    //Get input for a string until the user types "-1":
    cout << "Enter a data point (-1 to stop input):\n";
    getline(cin, datapoint);
    while (datapoint != "-1") {
        size_t commalocation = datapoint.find_first_of(',');

        //Validate input
        if (commalocation == string::npos) {
            try {throw runtime_error("No comma in string.");} 
            catch (const exception& e) {cout << "Error: " << e.what() << endl;}
        }
        else if (commalocation != datapoint.find_last_of(',')) {
            try {throw runtime_error("Too many commas in input.");} 
            catch (const exception& e) {cout << "Error: " << e.what() << endl;}
        }

        else {
            // Once validated, Split and validate second half of input
            try {
                int datapointpart2 = stoi(datapoint.substr(commalocation + 1));

                // Store separate pieces
                column1datatable.push_back(datapoint.substr(0, commalocation));
                column2datatable.push_back(datapointpart2);
                cout << "Data string: " << datapoint.substr(0, commalocation) << endl;
                cout << "Data integer: " << datapointpart2 << endl;
            } 
            catch (const invalid_argument&) {cout << "Error: Comma not followed by an integer." << endl;}
        }
        cout << "Enter a data point (-1 to stop input):\n";
        getline(cin, datapoint);
    }

    //Print out data in table format
    cout << "\n" << setw(33) << right << datatitle << endl;
    cout << setw(20) << left << column1 << "|" << setw(23) << right << column2 << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < column1datatable.size(); ++i) {
        cout << setw(20) << left << column1datatable[i] << "|" << setw(23) << right << column2datatable[i] << endl;
    }

    //Print out data in chart format
    cout << endl; 
    for (int i = 0; i < column1datatable.size(); ++i) {
        string asterisks(column2datatable[i], '*');
        cout << setw(20) << right << column1datatable[i] << " " << asterisks << endl;
    }

    return 0;
}