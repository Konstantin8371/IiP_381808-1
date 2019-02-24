#pragma once
#include <math.h>
#include <iostream>

using namespace std;


class Vector3D
{
private:
	double x1, y1, z1; // Koordinati nachalnoy tochki
	double x2, y2, z2; // Konechnoy tochki
	
public:
	Vector3D(); // konstruktor
	Vector3D(double x1, double x2, double y1, double y2, double z1, double z2); // s parametrami

	Vector3D operator= (const Vector3D& v2); //peregruzka operatora =
	Vector3D operator+ (const Vector3D& v2); //peregruzka +
	Vector3D operator- (const Vector3D& v2); //peregruzka -
	Vector3D operator* (const Vector3D& v2); //peregruzka *
	Vector3D operator* (double a); // dlya umnozheniya na konstantu
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

