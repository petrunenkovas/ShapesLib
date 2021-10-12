// ShapesClient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include "ShapesLib.h"
#define M_PI 3.14159265358979313846

using namespace std;

//function for radii comparison for circles
bool comp(Circle* a, Circle* b) {
	return a->GetR() < b->GetR();
}

int main() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> uid(0, 200);  //initialization of range for random generation of amount of shapes
	int Number = uid(gen);			//random amount of shapes
	vector<Circle*> Shapes;			//container for all shapes
	vector<Circle*> Circles;		//container for circles
	Circle* pCircle = 0;
	Ellipse* pEllipse = 0;
	Helix* pHelix = 0;
	for (int i = 0; i < Number; i++) {
		uniform_int_distribution<> uid(0, 2);
		uniform_real_distribution<> urd(-30, 30);
		Point NewPoint(urd(gen), urd(gen), urd(gen)); //generation of central point
		switch (uid(gen)) {			//random chose of the type of shape
		case 0:
			pCircle = new Circle(abs(urd(gen)), NewPoint);
			Shapes.push_back(pCircle);
			Circles.push_back(pCircle);
			break;
		case 1:
			pEllipse = new Ellipse(abs(urd(gen)), NewPoint, abs(urd(gen)));
			Shapes.push_back(pEllipse);
			break;
		case 2:
			pHelix = new Helix(abs(urd(gen)), NewPoint, abs(urd(gen)));
			Shapes.push_back(pHelix);
			break;
		}
	}
	//display of points and derivatives with given parameter t
	double t = M_PI / 4;
	for (auto s : Shapes) {
		cout << s->GetPoint(t).Getx() << " " << s->GetPoint(t).Gety() << " " << s->GetPoint(t).Getz() << " " << s->GetDerivative(t).Getx() << " " << s->GetDerivative(t).Gety() << " " << s->GetDerivative(t).Getz() << "\n";
	}
	//sorting of circles by radii
	sort(Circles.begin(), Circles.end(), comp);
	//sum of radii
	double SumR = 0;
#pragma omp parralel shared (Circle.GetR()) reduction (+: SumR) num_threads(2)
	{
#pragma omp for
		for (auto circle : Circles) {
			SumR += circle->GetR();
		}
	}
	cout << "Sum of circle radii = " << SumR;
	for_each(Shapes.begin(), Shapes.end(), default_delete<Circle>());
	return 0;
}