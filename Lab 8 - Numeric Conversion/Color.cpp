#include "Color.h"
#include <sstream>
#include <iomanip>

Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;
    hexValue = "000000";
    name = "Unnamed";
}

void Color::SetValue(int value)
{
    // Retrieve the individual color values from the integer using bit-shifting
    blue = value & 0xFF; // Bits 0-7
    green = (value >> 8) & 0xFF; // Bits 8-15
    red = (value >> 16) & 0xFF; // Bits 16-23

    // Convert the color values to hexadecimal string representation
    stringstream ss;
    ss << "0x" << setfill('0') << setw(2) << hex << static_cast<int>(red)
       << setfill('0') << setw(2) << hex << static_cast<int>(green)
       << setfill('0') << setw(2) << hex << static_cast<int>(blue);
    hexValue = ss.str();
}

void Color::SetName(const char* name)
{
    this->name = name;
}

unsigned char Color::GetR() const
{
    return red;
}

unsigned char Color::GetG() const
{
    return green;
}

unsigned char Color::GetB() const
{
    return blue;
}

string Color::GetHexValue() const
{
    string hexValueUpper = hexValue;
    // Convert the hexadecimal string (starting from the third character) to uppercase
    for (auto i = hexValueUpper.begin() + 2; i != hexValueUpper.end(); ++i)
    {
        *i = std::toupper(*i);
    }
    return hexValueUpper;
}

string Color::GetName() const
{
    return name;
}
