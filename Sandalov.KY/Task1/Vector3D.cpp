#include "Vector3D.h"


Vector3D::Vector3D() // konstruktor
{
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	z1 = 0;
	z2 = 0;
}

Vector3D::Vector3D(double _x1, double _x2, double _y1, double _y2, double _z1, double _z2) // s parametrami
{
	x1 = _x1;
	x2 = _x2;
	y1 = _y1;
	y2 = _y2;
	z1 = _z1;
	z2 = _z2;
}

Vector3D Vector3D::operator= (const Vector3D& v2) //peregruzka operatora =
{
	if (this != &v2)
	{
		x1 = v2.x1;
		x2 = v2.x2;
		y1 = v2.y1;
		y2 = v2.y2;
		z1 = v2.z1;
		z2 = v2.z2;
	}
	return* this;
}

Vector3D Vector3D::operator+ (const Vector3D& c2) //peregruzka +
{
	Vector3D tmp;
	tmp.x1 = x1 + c2.x1;
	tmp.x2 = x2 + c2.x2;
	tmp.y1 = y1 + c2.y1;
	tmp.y2 = y2 + c2.y2;
	tmp.z1 = z1 + c2.z1;
	tmp.z2 = z2 + c2.z2;
	return tmp;
}

Vector3D Vector3D::operator- (const Vector3D& c2)//peregruzka -
{
	Vector3D tmp;
	tmp.x1 = x1 - c2.x1;
	tmp.x2 = x2 - c2.x2;
	tmp.y1 = y1 - c2.y1;
	tmp.y2 = y2 - c2.y2;
	tmp.z1 = z1 - c2.z1;
	tmp.z2 = z2 - c2.z2;
	return tmp;
}

Vector3D Vector3D::operator* (const Vector3D& c2)//peregruzka *
{
	Vector3D tmp;
	tmp.x1 = x1 * c2.x1;
	tmp.x2 = x2 * c2.x2;
	tmp.y1 = y1 * c2.y1;
	tmp.y2 = y2 * c2.y2;
	tmp.z1 = z1 * c2.z1;
	tmp.z2 = z2 * c2.z2;
	return tmp;
}

Vector3D Vector3D::operator* (double a)// dlya umnozheniya na konstantu
{
	Vector3D tmp;
	tmp.x1 = x1 * a;
	tmp.x2 = x2 * a;
	tmp.y1 = y1 * a;
	tmp.y2 = y2 * a;
	tmp.z1 = z1 * a;
	tmp.z2 = z2 * a;
	return tmp;
}

bool Vector3D::operator== (const Vector3D& v2)// peregruzka ==
{
	return (lng(*this) == lng(v2));
}

bool Vector3D::operator!= (const Vector3D& v2)// peregruzka !=
{
	return (lng(*this) != lng(v2));
}

bool Vector3D::operator<= (const Vector3D& v2)// peregruzka <=
{
	return (lng(*this) <= lng(v2));
}

bool Vector3D::operator>= (const Vector3D& v2)// peregruzka >=
{
	return (lng(*this) >= lng(v2));
}

bool Vector3D::operator< (const Vector3D& v2)// peregruzka <
{
	return (lng(*this) < lng(v2));
}

bool Vector3D::operator> (const Vector3D& v2)// peregruzka >
{
	return (lng(*this) > lng(v2));
}

double Vector3D::lng(const Vector3D& v2)// schitaet dlinnu vectora
{
	return sqrt((v2.x2 - v2.x1)*(v2.x2 - v2.x1) + (v2.y2 - v2.y1)*(v2.y2 - v2.y1) + (v2.z2 - v2.z1)*(v2.z2 - v2.z1));
}

ostream& operator<< (ostream& stream, const Vector3D& v2)// peregruzka vivoda 
{
	stream << v2.x1 << endl << v2.x2 << endl << v2.y1 << endl << v2.y2 << endl << v2.z1 << endl << v2.z2;
	return stream;
}

istream& operator>> (istream& stream, Vector3D& v2)// peregruzka vvoda 
{
	stream >> v2.x1 >> v2.x2 >> v2.y1 >> v2.y2 >> v2.z1 >> v2.z2;
	return stream;
}