#pragma once
#include "Storage.h"

class CashBox
{
	Storage *strg; // указатель на объект класса склада
	int current_scan; // текущий отсканированный товар

	Position *check; // массив товаров, записанных в чеке
	int chCount; // количество элементов в чеке
	int chBuffSize; // буфер для чека

	double final_fullsum; // итоговая полная сумма
	double final_dissum; // с учетом скидки
	double final_diss; // суммарная скидка

public:
	CashBox(Storage *_strg); // конструктор с параметром(указатель на объект класа склад, чтобы иметь доступ к складу через кассу)
	CashBox(const CashBox& _csh); // конструктор копирования
	~CashBox(); // деструктор
	void CheckScan(const string& _str); // сканирование товара
	void ShowInf(); // вывод на консоль информации об отсканированном товаре
	void AddToCheck(); // добавление отсканированного товара в чек
	void DeleteFromCheck(int _cnt, int _rcount); // удаление выбранного товара из чека
	void GetCheck(int _count); // формирует чек за покупку(в виде файла)
	void ShowCheck(); // вывод информации о товарах из чека на консоль
	void CountSum(); // вывод информации об итоговой сумме на консоль
};

