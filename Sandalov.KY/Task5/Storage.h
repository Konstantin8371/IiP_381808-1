#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Position // структура, содержащая информацию о товарах со склада
{
	string barcode; // код товара
	string name; // наименование
	double cost; // стоимость
	int discount; // скидка
	int cnt; // остаток на складе
	int ch_cnt; // количество в чеке, нужно только для чека

};

class Storage
{
	Position *arrPos; // по сути масив товаров со склада
	int count; // количество элементов на складе

public:
	Storage(int _count); // контруктор с параметром, в данном случае задает количество элементов на складе
	~Storage(); // деструктор
	Position ReturnPos(int _cnt) { return arrPos[_cnt]; } // возвращает информацию о товаре, хранящемся в заданой ячейке
	void DeletePos(int _cnt); // уменьшет остаток товара на складе
	void AddPos(int _cnt) { arrPos[_cnt].cnt++; } // увеличивает остаток на складе
	int ShowCnt(int _cnt) { return arrPos[_cnt].cnt; } // возвращает остаток
	int FindPos(const string& _code); // возвращает позицию, ячейку, в которой хранится товар по его коду
	friend istream& operator>> (istream& _in, Storage& _strg); // перегрузка операций ввода и вывода из потока для класса
	friend ostream& operator<< (ostream& _out, const Storage& _strg);

};

ostream& operator<< (ostream& _out, const Position& _pos); //перегрузка операций ввода и вывода из потока для структуры
istream& operator>> (istream& _in, Position& _pos);