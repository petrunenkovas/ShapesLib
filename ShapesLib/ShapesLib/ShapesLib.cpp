// ShapesLib.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "ShapesLib.h"
#include "pch.h"
#include <cmath>
#define M_PI 3.14159265358979313846
using namespace std;

//class for 3D points
Point::Point(double x, double y, double z) : x(x), y(y), z(z)
	{}

SHAPESLIB_API double Point::Getx() {
	return x;
}

SHAPESLIB_API double Point::Gety() {
	return y;
}

SHAPESLIB_API double Point::Getz() {
	return z;
}

//class for circles is defined by radii a and central point o
Circle::Circle(double a, Point o) : a(a), o(o)
	{}

SHAPESLIB_API Point Circle::GetPoint(double t) {					//point on circle depends on parameter t
	double x = a * cos(t) + o.Getx();
	double y = a * sin(t) + o.Gety();
	Point newPoint(x, y, 0);
	return newPoint;
}

SHAPESLIB_API Point Circle::GetDerivative(double t) {				//partial derivatives at point with given parameter t
	double x = a * sin(t);
	double y = a * cos(t);
	Point newPoint(x, y, 0);
	return newPoint;
}

SHAPESLIB_API double Circle::GetR() {								//function for access to radii value
	return a;
}

//class for helixes is defined by radii a, central point o and period p
Helix:: Helix(double a, Point o, double p) : Circle(a, o), p(p)
{}

SHAPESLIB_API Point Helix::GetPoint(double t) {				//point on helix depends on parameter t
	double x = a * cos(t) + o.Getx();
	double y = a * sin(t) + o.Gety();
	double z = p * t / (2 * M_PI);
	Point newPoint(x, y, z);
	return newPoint;
}

SHAPESLIB_API Point Helix::GetDerivative(double t) {			//partial derivatives at point with given parameter t
	double x = a * sin(t);
	double y = a * cos(t);
	double z = p / (2 * M_PI);
	Point newPoint(x, y, z);
	return newPoint;
}

//class for ellipses is defined by two radii along X and Y axes - a and b, and central point o
Ellipse::Ellipse(double a, Point o, double b) : Circle(a, o), b(b)
{}

SHAPESLIB_API Point Ellipse::GetPoint(double t) {					//point on ellipse depends on parameter t
	double x = a * cos(t) + o.Getx();
	double y = b * sin(t) + o.Gety();
	Point newPoint(x, y, 0);
	return newPoint;
}

SHAPESLIB_API Point Ellipse::GetDerivative(double t) {			//partial derivatives at point with given parameter t
	double x = a * sin(t);
	double y = b * cos(t);
	Point newPoint(x, y, 0);
	return newPoint;
}
