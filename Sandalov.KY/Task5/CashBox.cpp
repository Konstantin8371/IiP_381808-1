#include "CashBox.h"



CashBox::CashBox(Storage *_strg) // конструктор с параметром(указатель на объект класа склад, чтобы иметь доступ к складу через кассу)
{
	strg = _strg;
	chCount = 0;
	chBuffSize = 0;
	current_scan = -1;
	final_fullsum = 0;
	final_dissum = 0;
}

CashBox::CashBox(const CashBox& _csh) // конструктор копирования
{
	final_fullsum = _csh.final_fullsum;
	final_dissum = _csh.final_dissum;
	strg = _csh.strg;
	current_scan = _csh.current_scan;
	chCount = _csh.chCount;
	chBuffSize = _csh.chBuffSize;
	check = new Position[chBuffSize];
	for (int i = 0; i < chCount; ++i)
		check[i] = _csh.check[i];
}

CashBox::~CashBox() // деструктор
{
	if (chCount != 0)
	{
		chCount = 0;
		chBuffSize = 0;
		delete[] check;
	}
	strg = nullptr;
	current_scan = -1;
	final_fullsum = 0;
	final_dissum = 0;
}

void CashBox::CheckScan(const string& _str) // сканирует товар
{
	for (int i = 0; i < _str.length(); ++i) // возбуждение исключения на случай некорректного ввода кода товара
	{
		if (_str[i] > 57 || _str[i] < 48)
			throw 1;
	}
	if (_str.length() != 4)
		throw 2;

	current_scan = strg->FindPos(_str); // в текущий отсканированный товар записывается информация, номер ячейки товара, код которого был прочитан(если такого товара нет, то присваивает -1)
	if (current_scan == -1)
		cout << "Такого товара нет на складе\n";
	else
		cout << "Такой товар имеется на складе\n";
}

void CashBox::ShowInf() // вывод на консоль информации об отсканированном товаре(если такой есть на складе)
{
	if (current_scan != -1)
		cout << "Код товара: " << strg->ReturnPos(current_scan).barcode << "; Наименование: " << strg->ReturnPos(current_scan).name << "; Стоимость: " << strg->ReturnPos(current_scan).cost << "руб.; Текущая скидка: " << strg->ReturnPos(current_scan).discount << "%; Остаток на складе: " << strg->ReturnPos(current_scan).cnt << '\n';
	else
		cout << "Товар не выбран\n";
}

void CashBox::AddToCheck() // добавление отсканированного товара в чек(если такой есть на складе)
{
	if (current_scan != -1)
	{
		if (strg->ShowCnt(current_scan) > 0) // проверка остатка на складе(если там 0, то добавление товара в чек не будет происходить)
		{
			for (int i = 0; i < chCount; ++i) // здесь он проверяет, есть ли уже данный товар в чеке, и если он там имеется, то просто увеличивает значение поля количество на 1 ед.
			{
				if (strg->ReturnPos(current_scan).barcode == check[i].barcode)
				{
					check[i].ch_cnt++; // увеличение значения поля количество
					double full_sum = check[i].cost; //и так же увеличивает общую стоимость без учета скидки и значение суммы к оплате
					final_fullsum += full_sum;
					final_dissum += full_sum * (100 - check[i].discount) / 100;
					strg->DeletePos(current_scan); // уменьшает количество товара на складе
					cout << "Товар успешно добавлен в чек\n";
					return;
				}
			}
			if (chBuffSize == chCount) // в случае, если буфер закончится, происходит выделение нового участка памяти необходимого размера и удаление старого(овобождение)
			{
				Position *tempArr;
				chBuffSize += 50;
				tempArr = new Position[chBuffSize];
				for (int i = 0; i < chCount; ++i)
				{
					tempArr[i] = check[i];
				}
				tempArr[chCount] = strg->ReturnPos(current_scan); 
				tempArr[chCount].ch_cnt++; // аналогично
				double full_sum = tempArr[chCount].cost;
				final_fullsum += full_sum;
				final_dissum += full_sum * (100 - tempArr[chCount].discount) / 100;
				strg->DeletePos(current_scan);
				chCount++;
				if (chCount > 1)
					delete[] check;
				check = tempArr;
				tempArr = nullptr;
			}
			else // в случае, если еще есть запас буфера
			{
				check[chCount] = strg->ReturnPos(current_scan);
				check[chCount].ch_cnt++;
				double full_sum = check[chCount].cost;
				final_fullsum += full_sum;
				final_dissum += full_sum * (100 - check[chCount].discount) / 100;

				strg->DeletePos(current_scan);
				chCount++;
			}
			cout << "Товар успешно добавлен в чек\n";
		}
		else
			cout << "Товар закончился на скдаде\n";
	}
}

void CashBox::DeleteFromCheck(int _cnt, int _rcount) // удаление товара из чека
{
	for (int i = 0; i < _rcount; ++i) // тут происходит поиск удаляемого товара на складе и увеличение остатка на единицу
	{
		if (check[_cnt - 1].barcode == strg->ReturnPos(i).barcode)
		{
			strg->AddPos(i);
			break;
		}
	}
	double full_sum = check[_cnt - 1].cost; //а здесь уменьшается общая стоимость без учета скидки и итоговая сумма к оплате
	final_fullsum -= full_sum;
	final_dissum -= full_sum * (100 - check[_cnt - 1].discount)/ 100;

	if (--check[_cnt - 1].ch_cnt == 0) // и в случае, если количество выбранного удаляемого товара в чеке равняется 0, просто все последующие после него товары переписываются на 1 место назад, то есть, просто уменьшение позиций в списке товаров в чеке на 1 со стиранием удаляемого товара
	{
		for (int i = _cnt - 1; i < chCount - 1; ++i)
			check[i] = check[i + 1];
		chCount--;
	}

}

void CashBox::GetCheck(int _count) // формирование чека за покупку
{
	ofstream ch("check.txt");
	for (int i = 0; i < chCount; ++i) // выводит в чек список позиций покупаемых товаров
		ch << i + 1 << ") " << "Код товара: " << check[i].barcode << "; Наименование: " << check[i].name << "; Стоимость: " << check[i].cost << "руб.; Количество: " << check[i].ch_cnt << "; Общая стоимость " << check[i].ch_cnt * check[i].cost << "руб.\n";
	if (final_fullsum > 0) // чтобы не делить на ноль надо проверять значение полной суммы
		final_diss = 100 - final_dissum * 100 / final_fullsum;
	else
	{
		final_diss = 0;
		ch << "Товары не выбраны\n";
	}
	// здесь выводит данные о сумме к оплате и полной стоимости
	ch << "Общая стоимость: " << final_fullsum << '\n';
	ch << "Суммарная скидка: " << final_diss << '\n';
	ch << "К оплате: " << final_dissum;
	ch.close();
	cout << "Чек за покупку успешно сформирован";
	// а после сохраниения чека надо собственно его очистить и так же подчистить всю инфу о полной стоимости и сумме к оплате
	delete[] check;
	chCount = 0;
	chBuffSize = 0;
	final_dissum = 0;
	final_dissum = 0;
	ofstream out("input.txt"); // да, тут еще он обновляет данные о наличии товаров на самом складе(файл input)
	out << _count << '\n';
	out << *strg;
	out.close();
}

void CashBox::ShowCheck() // выводит данные о позициях в чеке на консоль
{
	for (int i = 0; i < chCount; ++i)
		cout << i + 1 << ") " << "Код товара: " << check[i].barcode << "; Наименование: " << check[i].name << "; Стоимость: " << check[i].cost << "руб.; Количество: " << check[i].ch_cnt << "; Общая стоимость " << check[i].ch_cnt * check[i].cost << "руб.\n";
}

void CashBox::CountSum() // выводит информацию об итоговой сумме к оплате
{
	cout << "Итоговая сумма к оплате: " << final_dissum << '\n';
}