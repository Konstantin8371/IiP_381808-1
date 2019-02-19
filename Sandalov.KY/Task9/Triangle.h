#pragma once
#include <iostream>
using namespace std;

class Triangle
{
private:
	double a, b, c;
public:
	Triangle(double a, double b, double c): a(a), b(b), c(c) 
	{}
	bool true_triangle();
	void type_of_triangle();
	double ploshad();
	double perimetr();
	void resize(double a, double b, double c);
};

bool Triangle::true_triangle() {
	return (a + b > c && a + c > b && b + c > a);
}

void Triangle::type_of_triangle() {
	double max;
	double o1, o2;
	if (a > b)
		if (a < c)
		{
			max = c;
			o1 = b; o2 = a;
		}
		else
		{
			max = a;
			o1 = b; o2 = c;
		}
	else
		if (c > b)
		{
			max = c;
			o1 = a; o2 = b;
		}
		else
		{
			max = b;
			o1 = a; o2 = c;
		}
	if (max * max == o1 * o1 + o2 * o2)
		cout << "Этот трeугольник прямоугольный\n";
	else if (max * max > o1 * o1 + o2 * o2)
		cout << "Этот треугольник тупоугольный\n";
	else
		cout << "Этот треугольник остроугольный\n";
	return;
}

double Triangle::perimetr() {
	return a + b + c;	
}

double Triangle::ploshad() {
	double p = perimetr() / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

void Triangle::resize(double a, double b, double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}