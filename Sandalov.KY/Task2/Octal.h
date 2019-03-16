#pragma once
#include <iostream>
#include <string>

using namespace std;
// obyavlenie strukturi, kotoraya budet tipom isklucheniya
enum ExType {strNOTOCTA};
struct Exeption
{
	ExType ext;
	int pos;
	Exeption(ExType _ext, int _pos): ext(_ext), pos(_pos) {}
};

class Octal
{
	int size; // razmer massiva elementov tipa unsigned char
	int lng; // fakticheskaya dlina vos'merichnogo chisla
	unsigned char* octa; // ukazatel na mesto v pamyati, gde hranitsa massiv chisel vosmerichnogo chisla
public:
	Octal(); // konstruktor po umolchaniyu
	Octal(int _size); // konstruktor s zadavaemim razmerom massiva 
	Octal(const string& _str); // konstruktor preobrazovaniya tipa 
	Octal(const Octal& _oct); // konstruktor kopirovaniya
	// peregruzka operatorov
	Octal& operator= (const Octal& _oct);
	Octal operator+ (const Octal& _oct);
	Octal operator- (const Octal& _oct);
	Octal operator* (const Octal& _oct);
	bool operator== (const Octal& _oct);
	bool operator!= (const Octal& _oct);
	bool operator< (const Octal& _oct);
	bool operator>= (const Octal& _oct);
	bool operator> (const Octal& _oct);
	bool operator<= (const Octal& _oct);
	friend ostream& operator<< (ostream& stream, const Octal& _oct);
	friend istream& operator>> (istream& stream, Octal& _oct);
	// destruktor
	~Octal();
};