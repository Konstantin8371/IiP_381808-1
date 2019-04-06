#include "Dictionary.h"
#include <conio.h>
#include <locale>
#include <Windows.h>
#include <stdlib.h>

using namespace std;
void ShowCount(const Dictionary& _dict); // прототип функции, выводящей в консоль текущую длину словаря
void ShowMenu(); // прототип функции, выводящей в консоль главное меню программы

int main()
{
	Dictionary firstDict; // созается объект класса Dictionary
	SetConsoleCP(1251); //устанавливает кодировку ввода из консоли и из редактора кода
	SetConsoleOutputCP(1251); //устанавливает кодировку вывода на консоль
	ShowCount(firstDict); //прототип функции, показывающей число слов в словаре
	ShowMenu(); //прототип функции, выводящей на экран главное меню программы

	while(true) 
	{
		
		string menu;
		dt: // метка для оператора goto
		cout << "Выберите пункт меню: ";

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
			cout << "Такого пункта нет в меню" << endl;
			cout << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls"); // очищает консоль и заново выводит меню, переход к метке dt: 
			ShowCount(firstDict);
			ShowMenu();
			goto dt;
		}
		int mn = 0;
		for (int i = 0; i < menu.length(); ++i)
		{ 
			mn = mn * 10 + (int)(menu[i]) - 48;
		}
		string adr, newWord, newTrans; // переменные, отвечающие за ввод адреса файла, нового слова и его перевода соответственно
		string Y_N; // переменная, считывающая ответ пользователя на вопросы, где необходимо дать ответ[Yes/No/TryAgain]
		ifstream in; // переменные для работы с вводом выводом из файлов
		ofstream out;
		int cnt; // переменная, использующаяся при выборе одного из вариантов перевода слова
		switch (mn) // оператор switch, позволяющий реализовать выбор пункта меню
		{
		case 0: // выход из программы
			return 0; 

		case 1: // заполнение словаря из файла
			system("cls");
			ShowCount(firstDict);
			cout << "Укажите путь к файлу: ";
			cin >> adr;
			while (adr.find(".txt") == string::npos) // проверяет, есть ли в указанном пути ".txt"
			{
				cout << "Вы выбрали неправильный файл" << endl;
				cout << "Укажите путь к файлу: ";
				cin >> adr;
			}
			in.open(adr);
			
				in >> firstDict;
			
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 2: //добавление слова и его перевода в словарь
			point:
			system("cls");
			ShowCount(firstDict);
			ch:
			cout << "Введите слово, которое хотите добавить в словарь: ";
			
			cin >> newWord;
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
			{
			firstDict.ProverkaVvodaEng(newWord);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
				goto ch;
			}
			firstDict.AddWord(newWord);
			ch1:
			cout << "Введите его перевод: ";
			
			cin >> newTrans;
			
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв русского алфавита пытается вводить что-то еще
			{
			firstDict.ProverkaVvodaRus(newTrans);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы русского алфавита" << endl;
				goto ch1;
			}
			firstDict.AddTranslate(newTrans, firstDict.GetCount() - 1);
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 3: // добавление перевода слова в словарь
			system("cls");
			ShowCount(firstDict);
			ch0:
			cout << "Введите слово, перевод которого хотели бы добавить: ";
			cin >> newWord;
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
			{
				firstDict.ProverkaVvodaEng(newWord);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
				goto ch0;
			}
			while (firstDict.FindWord(newWord) == -1) // проверка условия вхождения слова, для которого будет добавлен перевод, в словарь, будет выполняьтся, пока не будет введено верное значение, или же пользователь не захочет прервать ввод слова, введя No или Yes, чтобы добавить слово, которого нет в словарь
			{
				cout << "Такого слова нет в словаре" << endl;
				cout << "Хотите добавить новое слово в словарь?[Yes/No/TryAgain]: ";
				cin >> Y_N;
				if (Y_N == "Yes")
					goto point;
				else if (Y_N == "No")
				{
					system("cls");
					ShowCount(firstDict);
					ShowMenu();
					goto dt;
				}
				cout << "Введите слово, перевод которого хотели бы добавить: ";
				cin >> newWord;
				try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
				{
					firstDict.ProverkaVvodaEng(newWord);
				}
				catch (int a)
				{
					cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
					goto ch0;
				}
			}
			ch2:
			cout << "Введите еще один вариант перевода данного слова: ";

			cin >> newTrans;
			
			try
			{
			firstDict.ProverkaVvodaRus(newTrans);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы русского алфавита" << endl;
				goto ch2;
			}
			firstDict.AddTranslate(newTrans, firstDict.FindWord(newWord)); // добавление еще одного варианта перевода слова
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 4: // изменение перевода слова в словаре
			system("cls");
			ShowCount(firstDict);
			ch3:
			cout << "Введите слово, перевод которого хотели бы поменять: ";
			cin >> newWord;
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
			{
				firstDict.ProverkaVvodaEng(newWord);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
				goto ch3;
			}
			
			while (firstDict.FindWord(newWord) == -1)
			{
				cout << "Такого слова нет в словаре" << endl;
				cout << "Хотите добавить новое слово в словарь?[Yes/No/TryAgain]: ";
				cin >> Y_N;
				if (Y_N == "Yes")
					goto point;
				else if (Y_N == "No")
				{
					system("cls");
					ShowCount(firstDict);
					ShowMenu();
					goto dt;
				}
				cout << "Введите слово, перевод которого хотели бы поменять: ";
				cin >> newWord;
				try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
				{
					firstDict.ProverkaVvodaEng(newWord);
				}
				catch (int a)
				{
					cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
					goto ch3;
				}
			}
			firstDict.ShowTranslate(firstDict.FindWord(newWord));
			cout << "Выберите номер того слова, которое хотели бы заменить: ";
			cin >> cnt;
			ch4:
			cout << "Введите новый вариант перевода: ";
			cin >> newTrans;
			
			try
			{
				firstDict.ProverkaVvodaRus(newTrans);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы русского алфавита" << endl;
				goto ch4;
			}
			firstDict.ChangeTranslate(firstDict.FindWord(newWord), newTrans, cnt); // изменение перевода выбранного слова в словаре
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 5: // узнать перевод слова
			system("cls");
			ShowCount(firstDict);
			ch5:
			cout << "Введите слово, перевод которого хотели бы узнать: ";
			cin >> newWord;
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
			{
				firstDict.ProverkaVvodaEng(newWord);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
				goto ch5;
			}
			while (firstDict.FindWord(newWord) == -1)
			{
				cout << "Такого слова нет в словаре" << endl;
				cout << "Хотите добавить новое слово в словарь?[Yes/No/TryAgain]: ";
				cin >> Y_N;
				if (Y_N == "Yes")
					goto point;
				else if (Y_N == "No")
				{
					system("cls");
					ShowCount(firstDict);
					ShowMenu();
					goto dt;
				}
				cout << "Введите слово, перевод которого хотели бы узнать: ";
				cin >> newWord;
				try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
				{
					firstDict.ProverkaVvodaEng(newWord);
				}
				catch (int a)
				{
					cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
					goto ch5;
				}
			}
			cout << "Перевод указанного слова: " <<endl;
			firstDict.ShowTranslate(firstDict.FindWord(newWord)); // показывает переводы выбранного слова()
			
			cout << endl <<"Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 6: // проверяет наличие слова в словаре
			system("cls");
			ShowCount(firstDict);
			ch6:
			cout << "Введите слово, о наличии которого хотели бы узнать: ";
			cin >> newWord;
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
			{
				firstDict.ProverkaVvodaEng(newWord);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
				goto ch6;
			}
			while (firstDict.FindWord(newWord) == -1)
			{
				cout << "Такого слова нет в словаре" << endl;
				cout << "Хотите добавить новое слово в словарь?[Yes/No/TryAgain]: ";
				cin >> Y_N;
				if (Y_N == "Yes")
					goto point;
				else if (Y_N == "No")
				{
					system("cls");
					ShowCount(firstDict);
					ShowMenu();
					goto dt;
				}
				cout << "Введите слово, о наличии которого хотели бы узнать: ";
				cin >> newWord;
				try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв английского алфавита пытается вводить что-то еще
				{
					firstDict.ProverkaVvodaEng(newWord);
				}
				catch (int a)
				{
					cout << "Необходимо ввести слово, используя только буквы английского алфавита" << endl;
					goto ch6;
				}
			}
			cout << "Такое слово есть в словаре";
			cout << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 7: // сохраняет словарь в файл
			system("cls");
			ShowCount(firstDict);
			out.open("output.txt");
			out << firstDict; // сохраняет словарь в файл
			cout << "Файл успешно сохранен" << endl;
			cout << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		case 8: // выводит словарь целиком в консоли
			system("cls");
			ShowCount(firstDict);
			cout << firstDict;
			cout << endl << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;

		default:
			system("cls");
			cout << "Такого пункта нет в меню" << endl;
			cout << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			ShowCount(firstDict);
			ShowMenu();
			break;
		}

	}
}

void ShowCount(const Dictionary& _dict) //функция, выводящая в консоль текущую длину словаря
{

	cout << endl << "Длина текущего словаря: " << _dict.GetCount() << endl << endl;
}

void ShowMenu() //функция, выводящая на экран главное меню программы
{
	cout << "1) Считать словарь из файла" << endl;
	cout << "2) Добавить слово в словарь" << endl;
	cout << "3) Добавить перевод слова в словарь" << endl;
	cout << "4) Изменить перевод слова в словаре" << endl;
	cout << "5) Узнать перевод слова" << endl;
	cout << "6) Проверить наличие слова в словаре" << endl;
	cout << "7) Сохранить словарь в файл" << endl;
	cout << "8) Вывести на экран весь словарь" << endl;
	cout << "0) Закрыть программу" << endl;
}