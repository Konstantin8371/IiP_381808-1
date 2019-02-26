#pragma once
#include <math.h>
#include <iostream>

using namespace std;


class Vector3D
{
private:
	double x, y, z; // Koordinati vectora
	
public:
	Vector3D(); // konstruktor
	Vector3D(double x2, double y2, double z2); // s parametrami

	Vector3D& operator= (const Vector3D& v2); //peregruzka operatora =
	Vector3D operator+ (const Vector3D& v2); //peregruzka +
	Vector3D operator- (const Vector3D& v2); //peregruzka -
	double operator* (const Vector3D& v2); //peregruzka *
	friend Vector3D operator* (double d, const Vector3D& v2); // dlya umnozheniya skalyara na vector
	bool operator== (const Vector3D& v2); // peregruzka ==
	bool operator!= (const Vector3D& v2); // peregruzka !=
	bool operator<= (const Vector3D& v2); // peregruzka <=
	bool operator>= (const Vector3D& v2); // peregruzka >=
	bool operator< (const Vector3D& v2); // peregruzka <
	bool operator> (const Vector3D& v2); // peregruzka >

	double lng(const Vector3D& v2); // schitaet dlinnu vectora

	friend ostream& operator<< (ostream& stream, const Vector3D& v2); // peregruzka vivoda i vvoda
	friend istream& operator>> (istream& stream, Vector3D& v2);


};

