#include "Vector3D.h"


Vector3D::Vector3D() // konstruktor
{

	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(double x2, double y2, double z2) // s parametrami
{
	x = x2;
	y = y2;
	z = z2;
}

Vector3D& Vector3D::operator= (const Vector3D& v2) //peregruzka operatora =
{
	if (this != &v2)
	{
		x = v2.x;
		y = v2.y;
		z = v2.z;
	}
	return* this;
}

Vector3D Vector3D::operator+ (const Vector3D& v2) //peregruzka +
{
	Vector3D tmp;
	tmp.x = x + v2.x;
	tmp.y = y + v2.y;
	tmp.z = z + v2.z;
	return tmp;
}

Vector3D Vector3D::operator- (const Vector3D& v2)//peregruzka -
{
	Vector3D tmp;
	tmp.x = x - v2.x;
	tmp.y = y - v2.y;
	tmp.z = z - v2.z;
	return tmp;
}

double Vector3D::operator* (const Vector3D& v2)//peregruzka *
{
	
	return (x*v2.x + y*v2.y + z*v2.z);
}

Vector3D operator* (double d, const Vector3D& v2)// umnozhenie skalyara na vektor
{
	Vector3D tmp;
	tmp.x = d * v2.x;
	tmp.y = d * v2.y;
	tmp.z = d * v2.z;
	return tmp;
}

bool Vector3D::operator== (const Vector3D& v2)// peregruzka ==
{
	return (lng(*this) == lng(v2));
}

bool Vector3D::operator!= (const Vector3D& v2)// peregruzka !=
{
	return !(*this == v2);
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
	return !(*this >= v2);
}

bool Vector3D::operator> (const Vector3D& v2)// peregruzka >
{
	return !(*this <= v2);
}

double Vector3D::lng(const Vector3D& v2)// schitaet dlinnu vectora
{
	return sqrt((v2.x)*(v2.x) + (v2.y)*(v2.y) + (v2.z)*(v2.z));
}

ostream& operator<< (ostream& stream, const Vector3D& v2)// peregruzka vivoda 
{
	stream << v2.x << endl << v2.y << endl << v2.z << endl;
	
	return stream;
}

istream& operator>> (istream& stream, Vector3D& v2)// peregruzka vvoda 
{
	stream >> v2.x >> v2.y >> v2.z;
	
	return stream;
}