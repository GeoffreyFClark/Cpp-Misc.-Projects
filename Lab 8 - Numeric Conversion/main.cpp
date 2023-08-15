#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "Color.h"
using namespace std;

void ReadFile(const char* filename, map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);

int main()
{
    cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
    cout << "7. Load all 6 files" << endl;
    int choice;
    cin >> choice;

    map<string, Color> colors;
    if (choice >= 1 && choice <= 6)
    {
        string file = "colors" + to_string(choice) + ".txt";
        ReadFile(file.c_str(), colors);
    }
    else if (choice == 7)
    {
        for (int i = 1; i <= 6; i++)
        {
            string file = "colors" + to_string(i) + ".txt";
            ReadFile(file.c_str(), colors);
        }
    }

    // Secondary menu
    cout << "1. Show all colors" << endl;
    cout << "2. Search for a color" << endl;
    cin >> choice;

    if (choice == 1)
        PrintColors(colors);
    else if (choice == 2)
        SearchForColor(colors);
    return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        string name;
        int value;

        // Parse the line to extract color name and value
        istringstream iss(line);
        if (!(iss >> name >> value))
            continue;

        Color color;
        color.SetValue(value);
        color.SetName(name.c_str());

        colors[name] = color;
    }

    file.close();
}

void PrintColors(const map<string, Color>& colors)
{
    for (const auto& entry : colors)
    {
        PrintColor(entry.second);
    }
    cout << "Number of colors: " << colors.size() << endl;
}

void PrintColor(const Color& color)
{
    cout << left << setw(20) << color.GetName();
    cout << right << setw(10) << color.GetHexValue();
    cout << "\t\t" << static_cast<int>(color.GetR()) << ","
         << static_cast<int>(color.GetG()) << ","
         << static_cast<int>(color.GetB()) << endl;
}

void SearchForColor(map<string, Color>& colors)
{
    string searchColor;
    // cout << "Enter the color name to search for: ";
    cin >> searchColor;

    auto it = colors.find(searchColor);
    if (it != colors.end())
    {
        // cout << "Found color:" << endl;
        PrintColor(it->second);
    }
    else
    {
        cout << searchColor << " not found!" << endl;
    }
}
