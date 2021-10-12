// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа SHAPESLIB_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции SHAPESLIB_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef SHAPESLIB_EXPORTS
#define SHAPESLIB_API __declspec(dllexport)
#else
#define SHAPESLIB_API __declspec(dllimport)
#endif
#pragma once

#ifdef SHAPESLIBRARY_EXPORTS
#define SHAPESLIBRARY_API __declspec(dllexport)
#else
#define SHAPESLIBRARY_API __declspec(dllimport)
#endif 

//class for 3D points
class SHAPESLIB_API Point {
public:
	explicit Point(double x, double y, double z);

	double Getx();
	double Gety();
	double Getz();

private:
	double x;
	double y;
	double z;
};

//class for circles is defined by radii a and central point o
class SHAPESLIB_API Circle {
public:
	explicit Circle(double a, Point o);

	virtual Point GetPoint(double t);					//point on circle depends on parameter t

	virtual Point GetDerivative(double t);				//partial derivatives at point with given parameter t

	double GetR();								//function for access to radii value

protected:
	double a;
	Point o;
};

//class for helixes is defined by radii a, central point o and period p
class SHAPESLIB_API Helix : public Circle {
public:
	explicit Helix(double a, Point o, double p);

	Point GetPoint(double t);				//point on helix depends on parameter t

	Point GetDerivative(double t);		//partial derivatives at point with given parameter t

private:
	double p;
};

//class for ellipses is defined by two radii along X and Y axes - a and b, and central point o
class SHAPESLIB_API Ellipse : public Circle {
public:
	explicit Ellipse(double a, Point o, double b);

	Point GetPoint(double t);				//point on ellipse depends on parameter t

	Point GetDerivative(double t);		//partial derivatives at point with given parameter t

private:
	double b;
};

