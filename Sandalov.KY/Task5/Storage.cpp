#include "Storage.h"



Storage::Storage(int _count) // контруктор с параметром, в данном случае задает количество элементов на складе
{
	count = _count;
	arrPos = new Position[count];
}


Storage::~Storage() // деструктор
{
	if (count != 0)
	{
		count = 0;
		delete[] arrPos;
	}
}

void Storage::DeletePos(int _cnt) // уменьшет остаток товара на складе
{
	if (arrPos[_cnt].cnt > 0) 
		arrPos[_cnt].cnt--;
}

int Storage::FindPos(const string& _code) // возвращает позицию, ячейку, в которой хранится товар по его коду
{
	for (int i = 0; i < count; ++i)
		if (_code == arrPos[i].barcode)
			return i;
	return -1; // в случае, если такого товара нет на складе
}

istream& operator>> (istream& _in, Storage& _strg) // перегрузка операций ввода и вывода из потока для класса
{
	for (int i = 0; i < _strg.count; ++i)
	{
		_in >> _strg.arrPos[i];
	}
	return _in;
}
ostream& operator<< (ostream& _out, const Storage& _strg)
{
	for (int i = 0; i < _strg.count - 1; ++i)
	{
		_out << _strg.arrPos[i] << '\n';
	}
	_out << _strg.arrPos[_strg.count - 1];
	return _out;
}

ostream& operator<< (ostream& _out, const Position& _pos) //перегрузка операций ввода и вывода из потока для структуры
{
	_out << _pos.barcode << '\n' << _pos.name << '\n' << _pos.cost << '\n' << _pos.discount << '\n' << _pos.cnt;
	return _out;
}
istream& operator>> (istream& _in, Position& _pos)
{
	_in >> _pos.barcode >> _pos.name >> _pos.cost >> _pos.discount >> _pos.cnt;
	_pos.ch_cnt = 0;
	return _in;
}