#include "Shapes.h"

// Shape2D class

void Shape2D::ShowArea() const
{
    cout << "The area of the " << GetName() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const
{
    return Area() > rhs.Area();
}

bool Shape2D::operator<(const Shape2D &rhs) const
{
    return Area() < rhs.Area();
}

bool Shape2D::operator==(const Shape2D &rhs) const
{
    return Area() == rhs.Area();
}

// Shape3D class

void Shape3D::ShowVolume() const
{
    cout << "The volume of the " << GetName() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const
{
    return Volume() > rhs.Volume();
}

bool Shape3D::operator<(const Shape3D &rhs) const
{
    return Volume() < rhs.Volume();
}

bool Shape3D::operator==(const Shape3D &rhs) const
{
    return Volume() == rhs.Volume();
}

// Square class

Square::Square() : side(0) {}

Square::Square(float side) : side(side) {}

void Square::Scale(float scaleFactor)
{
    side *= scaleFactor;
}

void Square::Display() const
{
    cout << "The area of the " << GetName() << "is : " << Area() << endl;
    cout << "Length of a side: " << side << endl;
}

float Square::Area() const
{
    return side * side;
}

string Square::GetName() const
{
    return "Square";
}

// Triangle class

Triangle::Triangle() : base(0), height(0) {}

Triangle::Triangle(float base, float height) : base(base), height(height) {}

void Triangle::Scale(float scaleFactor)
{
    base *= scaleFactor;
    height *= scaleFactor;
}

void Triangle::Display() const
{
    cout << "The area of the " << GetName() << "is : " << Area() << endl;
    cout << "Base: " << base << endl;
    cout << "Height: " << height << endl;
}

float Triangle::Area() const
{
    return 0.5f * base * height;
}

string Triangle::GetName() const
{
    return "Triangle";
}

// Circle class

Circle::Circle() : radius(0) {}

Circle::Circle(float radius) : radius(radius) {}

void Circle::Scale(float scaleFactor)
{
    radius *= scaleFactor;
}

void Circle::Display() const
{
    cout << "The area of the " << GetName() << "is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

float Circle::Area() const
{
    return PI * radius * radius;
}

string Circle::GetName() const
{
    return "Circle";
}

// TriangularPyramid class

TriangularPyramid::TriangularPyramid() : Shape3D(), base(0.0f), height(0.0f), pyramidHeight(0.0f) {}

TriangularPyramid::TriangularPyramid(float base, float height, float pyramidHeight) 
    : Shape3D(), base(base), height(height), pyramidHeight(pyramidHeight) {}


void TriangularPyramid::Scale(float scaleFactor)
{
    base *= scaleFactor;
    height *= scaleFactor;
    pyramidHeight *= scaleFactor;
}

void TriangularPyramid::Display() const
{
    cout << "The volume of the " << GetName() << " is : " << Volume() << endl;
    cout << "The height is: " << base << endl;
    cout << "The area of the Triangle is: " << pyramidHeight*height/2.0f << endl;
    cout << "Base: " << height << endl;
    cout << "Height: " << pyramidHeight << endl;
}

float TriangularPyramid::Volume() const
{
    return (base * height * pyramidHeight) / 6.0f;
}

string TriangularPyramid::GetName() const
{
    return "Triangular Pyramid";
}

// Cylinder class

Cylinder::Cylinder() : Shape3D(), height(0.0f), radius(0.0f) {}

Cylinder::Cylinder(float height, float radius) : Shape3D(), height(height), radius(radius) {}

void Cylinder::Scale(float scaleFactor)
{
    height *= scaleFactor;
    radius *= scaleFactor;
}

void Cylinder::Display() const
{
    cout << "The volume of the " << GetName() << "is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    cout << "The area of the Circle is : " << PI * radius * radius << endl;
    cout << "Radius: " << radius << endl;
}

float Cylinder::Volume() const
{
    return PI * radius * radius * height;
}

string Cylinder::GetName() const
{
    return "Cylinder";
}

// Sphere class

Sphere::Sphere() : Shape3D(), radius(0.0f) {}

Sphere::Sphere(float radius) : Shape3D(), radius(radius) {}

void Sphere::Scale(float scaleFactor)
{
    radius *= scaleFactor;
}

void Sphere::Display() const
{
    cout << "The volume of the " << GetName() << "is : " << Volume() << endl;
    cout << "The area of the Circle is : " << PI * radius * radius << endl;
    cout << "Radius: " << radius << endl;
}

float Sphere::Volume() const
{
    return (4.0f / 3.0f) * PI * radius * radius * radius;
}

string Sphere::GetName() const
{
    return "Sphere";
}
