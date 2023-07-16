#include <iostream>
#include <string>

using namespace std;

#define PI 3.14159f

class Shape
{
public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
    virtual ~Shape() {}
};

class Shape2D : public virtual Shape
{
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName() const = 0;

    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
};

class Shape3D : public virtual Shape
{
public:
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName() const = 0;

    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class Square : public Shape2D
{
private:
    float side;

public:
    Square();
    Square(float side);

    void Scale(float scaleFactor) override;
    void Display() const override;
    float Area() const override;
    string GetName() const override;
};

class Triangle : public Shape2D
{
private:
    float base;
    float height;

public:
    Triangle();
    Triangle(float base, float height);

    void Scale(float scaleFactor) override;
    void Display() const override;
    float Area() const override;
    string GetName() const override;
};

class Circle : public Shape2D
{
private:
    float radius;

public:
    Circle();
    Circle(float radius);

    void Scale(float scaleFactor) override;
    void Display() const override;
    float Area() const override;
    string GetName() const override;
};

class TriangularPyramid : public Shape3D
{
private:
    float base;
    float height;
    float pyramidHeight;
public:
    TriangularPyramid();
    TriangularPyramid(float base, float height, float pyramidHeight);

    void Scale(float scaleFactor) override;
    void Display() const override;
    float Volume() const override;
    string GetName() const override;
};

class Cylinder : public Shape3D
{
private:
    float height;
    float radius;
public:
    Cylinder();
    Cylinder(float height, float radius);
    void Scale(float scaleFactor) override;
    void Display() const override;
    float Volume() const override;
    string GetName() const override;
};

class Sphere : public Shape3D
{
private:
    float radius;
public:
    Sphere();
    Sphere(float radius);
    void Scale(float scaleFactor) override;
    void Display() const override;
    float Volume() const override;
    string GetName() const override;
};
