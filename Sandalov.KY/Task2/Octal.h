#pragma once
#include <iostream>
#include <string>

using namespace std;
// объявление структуры, которая будет типом исключения
enum ExType {strNOTOCTA};
struct Exeption
{
	ExType ext;
	int pos;
	Exeption(ExType _ext, int _pos): ext(_ext), pos(_pos) {}
};

class Octal
{
	int size; // размер массива элементов типа unsigned char
	int lng; // фактическая длина восьмеричного числа
	unsigned char* octa; // указатель на память, где хранится массив цифр восьмеричного числа
public:
	Octal(); // конструктор по умолчанию
	Octal(int _size); // конструктор с задаваемым размером массива 
	Octal(const string& _str); // конструктор преобразования типа из строки 
	Octal(const Octal& _oct); // конструктор копирования
	// перегрузка операторов
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
	// деструктор 
	~Octal();
};