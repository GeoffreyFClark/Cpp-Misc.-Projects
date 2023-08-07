#include <string>
using namespace std;

class Color
{
public:
    // Default constructor
    Color();

    // Given an integer value, convert it to RGB and Hex values
    void SetValue(int value);

    // Set the name of the color
    void SetName(const char* name);

    // Accessors
    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;
    string GetHexValue() const;
    string GetName() const;

private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    string hexValue;
    string name;
};