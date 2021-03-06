#include "CashBox.h"
#include <conio.h>

void Menu(); // прототип функции вывода меню на консоль
void CurrentItem(CashBox _cash); // прототип функции вывода информации о текущем отсканированном товаре и суммарной сумме к оплате
int StrToInt(const string& _str); // прототип функции перевода значения строоковой переменной, содержащей информацию о числе в переменную типа int
int main() {
	setlocale(LC_ALL, "Russian");
	int count; // число позиций на складе
	ifstream in("input.txt"); // получаем доступ к файлу, из которого считываем информацию о числе позиций на складе и о каждой отдельной позиции
	in >> count;
	Storage a(count);
	in >> a; // сситываем информацию о товаре на складе
	in.close();
	CashBox b(&a); // передаем ссылку на склад в кассу, чтобы можно было с ним через нее взаимодейстоввать
	string code; // переменная для считывания кода сканируемых товаров

	int del;
	while (true)
	{
		string menu;
		CurrentItem(b);
		Menu();

		try // обработчик исключения, которое возникает в том случае, если пользователь вместо числа в выборе пункта меею будет пытаться вводить нечисловые символы
		{
			cin >> menu;
			for (int i = 0; i < menu.length(); ++i)
			{
				if (menu[i] > 57 || menu[i] < 48)
					throw 1;
			}
		}
		catch (int a)
		{
			system("cls");
		}
		int mn = StrToInt(menu); // фукция перевода значения строоковой переменной, содержащей информацию о числе в переменную типа int
		
		switch (mn)
		{
		case 0: // выход из кассы
		{
			return 0;
		}
		case 1: // сканироание кода очередного товара
		{
			system("cls");
			cout << "Введите код товара: ";
			cin >> code;
			try // исключение на случай ввода нечисловых символов вместо кода или же кода некорректной длины
			{
				b.CheckScan(code); // функция проверяет, есть ли такой товар на кладе
			}
			catch (int a)
			{
				system("cls");
				if (a == 2)
					cout << "Нужно ввести 4! числовых сомвола кода";
				if (a == 1)
					cout << "Вы ввели нечисловые символы";
				cout << '\n' << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
				_getch();
				system("cls"); // очищает консоль и заново выводит меню, переход к метке dt: 
				break;
			}

			cout << "Для продолжения оформления покупки нажмите Enter";
			_getch();
			system("cls");
			break;
		}
		case 2: // добавляет выбранный товар в чек
		{
			system("cls");
			b.AddToCheck(); // метод, добавляющий товар в чек
			cout << "Для продолжения оформления покупки нажмите Enter\n";
			_getch();
			system("cls");
			break;
		}
		case 3: // функция, формирующая чек и сохраняющая его в файл
		{
			system("cls");
			b.GetCheck(count);
			cout << "Для продолжения оформления покупки нажмите Enter\n";
			_getch();
			system("cls");
			break;
		}
		case 4: // удаляет выбранный товар из чека
		{
			system("cls");
			b.ShowCheck();
			cout << "Выберите товар, который хотите удалить: ";
			cin >> del;
			b.DeleteFromCheck(del, count);
			cout << "Для продолжения оформления покупки нажмите Enter\n";
			_getch();
			system("cls");
			break;
		}
		default: // на случай ввода несуществующего пункта меню
			system("cls");
			cout << "Такого пункта нет в меню\n" ;
			cout << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			break;
		}

	}
	_getch();
	return 0;
}

void Menu() // функция выводит меню на консоль
{
	cout << "1) Сканировать товар\n";
	cout << "2) Добавить данные о товаре в чек\n";
	cout << "3) Сформировать чек за покупку\n";
	cout << "4) Удалить выбранный товар из покупки\n";
	cout << "0) Закрыть кассу\n";
	cout << "выберите нужный пункт меню: ";
}

void CurrentItem(CashBox _cash) // функция выводит на консоль информацию о текущем отсканированном товаре и итоговой сумме к оплате
{
	_cash.ShowInf();
	_cash.CountSum();
	cout << '\n';
}

int StrToInt(const string& _str) // фукция перевода значения строоковой переменной, содержащей информацию о числе в переменную типа int
{
	int sum = 0;
	for (int i = 0; i < _str.length(); ++i)
	{
		sum = sum * 10 + (_str[i] - '0');
	}
	return sum;
}