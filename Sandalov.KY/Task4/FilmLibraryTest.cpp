#include "FilmLibrary.h"
#include <conio.h>
#include <fstream>
#include <Windows.h>

void ShowMenu(); // прототип функции, выводящей в консоль главное меню программы
void ShowCount(FilmLib _flmlb); // прототип функции, выводящей в консоль текущую длину словаря
Film InputNewFilm(); // прототип функции, 

int main()
{
	SetConsoleCP(1251); //устанавливает кодировку ввода из консоли и из редактора кода
	SetConsoleOutputCP(1251); //устанавливает кодировку вывода на консоль
	
	FilmLib first_lib; // созается объект класса FilmLib
	Film input; // переменная типа Film, которая используется для ввода информации о новом фильме
	
	while (true)
	{
		string menu; // с использованием данной переменной осуществляется выбор пункта меню
	dt: // метка для оператора goto
		ShowCount(first_lib);
		ShowMenu();
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
			cout << "Такого пункта нет в меню" << '\n';
			cout << '\n' << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls"); // очищает консоль и заново выводит меню, переход к метке dt: 
			goto dt; // переход к метке dt:
		}

		int mn = StrToInt(menu); // фукция перевода значения строоковой переменной, содержащей информацию о числе в переменную типа int

		string adr, name; // adr используется для ввода пути, по которому расп. файл словаря, name - считывание имени режиссера или названия фильма
		string Y_N; // переменная, считывающая ответ пользователя на вопросы
		ifstream in;  // переменные для работы с
		ofstream out; // вводом выводом из файлов
		int cnt = 0, year;
		Film *Arr = NULL;

		switch (mn) // оператор switch, позволяющий реализовать выбор пункта меню
		{
		case 0: // выход из программы

			return 0;

		case 1: // заполнение фильмотеки из файла

			system("cls");
			ShowCount(first_lib);
			cout << "Укажите путь к файлу: ";
			cin >> adr;
			while (adr.find(".txt") == string::npos) // проверяет, есть ли в указанном пути ".txt"
			{
				cout << "Вы выбрали неправильный файл" << '\n';
				cout << "Укажите путь к файлу: ";
				cin >> adr;
			}
			in.open(adr);

			in >> first_lib;

			system("cls");
			break;

		case 2: // сохраняет фильмотеку в файл

			system("cls");
			ShowCount(first_lib);
			out.open("output.txt");
			out << first_lib;
			cout << "Файл успешно сохранен" << '\n';
			cout << '\n' << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			break;

		case 3:  // добавление нового фильма в фильмотеку

			system("cls");
			ShowCount(first_lib);
			input = InputNewFilm();
			first_lib.AddFilm(input);

			break;

		case 4: // осуществляет поиск фильма по названию, ели фильмов с одинаковым названием несколько, то, выводит все и представляет возможность удалить фильм, который нашли по названию или же изменить его данные
			    // да, объединил несколько пунктов, так как везде в них осуществляется одно и то же действие, поиск по названию(ну и дате прьемьеры, собственно, так как могут быть фильмы с одинаковыми названиями)
			system("cls");
			ShowCount(first_lib);
		ch1:
			cout << "Введите имя фильма, который хотели бы найти: ";
			cin.ignore();
			getline(cin, name);
			try //обработчик исключения, которое возникает в том случае, если пользователь вмето букв русского алфавита и цифр пытается вводить что-то еще
			{
				first_lib.ProverkaVvodaRus(name);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы русского алфавита" << endl;
				goto ch1;
			}
			if (first_lib.NameSearch(name) == -1) // если такого фильма нет в фильмотеке, выводит соответствующее сообщение 
			{
				cout << "Такого фильма нет в фильмотеке" << '\n';
				
			}
			else // в противном случае, выводит все фильмы с одинаковым названием в консоли
			{
				cnt = 0;
				while (first_lib.GetFilm(first_lib.NameSearch(name) + cnt).name == first_lib.GetFilm(first_lib.NameSearch(name)).name)
				{
					cout << cnt + 1 << ") " << first_lib.GetFilm(first_lib.NameSearch(name) + cnt) << '\n';
					cnt++;
				}

				cout << "Хотите изменить данные фильма?[Yes/No]: "; // предоставляет возможность поменять или удалить выбранный из выведенного списка любой фильм 
				cin >> Y_N;
				if (Y_N == "Yes")
				{
					cout << "Выберите номер того фильма, данные которого хотели бы поменять: ";
					cin >> cnt;
					cout << "Ваши дальнейшие дейтвия" << '\n';
					cout << "1) Удалить фильм" << '\n';
					cout << "2) Поменять данные фильма" << '\n';
					cout << "Введите номер нужного пункта: ";
					cin >> Y_N;
					if (Y_N == "2")
					{
						first_lib.ChangeSelectedFilm(InputNewFilm(), first_lib.NameSearch(name) + cnt - 1);
					}
					else
					{
						first_lib.DeleteSelectedFilm(first_lib.NameSearch(name) + cnt - 1);
					}
					cout << "Данные о фильме изменены";
				}
			}
			cout << '\n' << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			break;

		case 5: // выводит все фильмы выбранного режисера, если такие есть
			system("cls");
			ShowCount(first_lib);
		ch2:
			cout << "Введите имя режиссера, фильмы которого хотели бы найти: ";
			cin.ignore();
			getline(cin, name);
			try
			{
				first_lib.ProverkaVvodaRus(name);
			}
			catch (int a)
			{
				cout << "Необходимо ввести слово, используя только буквы русского алфавита" << endl;
				goto ch2;
			}
			Arr = first_lib.ProducerSearch(name, &cnt, Arr);
			if (cnt == 0)
			{
				cout << "Фильмов такого режиссера в фильмотеке нет" << '\n';
				
			}
			else
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 6: // Выводит все фильмы, вышедшие в прокат в выбранном году, если такие есть
			system("cls");
			ShowCount(first_lib);
			cout << "Введите год, чтобы посмотреть, какие в это время вышли фильмы: ";
			cin >> year;
			Arr = first_lib.TimeSearch(year, &cnt, Arr);
			if (cnt == 0)
			{
				cout << "Фильмов этого года в фильмотеке нет" << '\n';
				
			}
			else
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 7: // выдает заданное число фильмов с максимальными сборами
			system("cls");
			ShowCount(first_lib);
			cout << "Введите число фильмов с наибольшими сборами, которое хотели бы вывести на экран: ";
			cin >> cnt;
			Arr = new Film[cnt];
			first_lib.MaxBoxOffice(&cnt, Arr);
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 8: // выдает заданное число фильмов с максимальными сборами вышедшие в определенном году
			system("cls");
			ShowCount(first_lib);
			cout << "Введите год: ";
			cin >> year;
			cout << "Введите число фильмов с наибольшими сборами в выбранном году, которое хотели бы вывести на экран: ";
			cin >> cnt;
			
			Arr = new Film[cnt];
			first_lib.MaxBoxOffice(&cnt, Arr, year);
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		default: // выводит сообщение о том, что такого пункта меню нет, если не будет вызван ни один из кейсов
			system("cls");
			cout << "Такого пункта нет в меню" << endl;
			cout << endl << "Чтобы вернуться на главный экран, нажмите на клавишу Enter";
			_getch();
			system("cls");
			break;
		}

	}
}

void ShowMenu() // функция вывода меню в консоль
{

	cout << "1) Считать фильмотеку из файла" << '\n';
	cout << "2) Сохранить фильмотеку в файл" << '\n';
	cout << "3) Добавить фильм в фильмотеку" << '\n';
	cout << "4) Найт нужный фильм, удалить/изменить его" << '\n';
	cout << "5) Выдать все фильмы заданного режиссера" << '\n';
	cout << "6) Выдать ве фильмы, вышедшие в прокат в выбранном году" << '\n';
	cout << "7) Выдать заданное число фильмов с наибольшими сборами" << '\n';
	cout << "8) Выдать заданное число фильмов с наибольшими сборами в выбранном году" << '\n';
	cout << "0) Выйти из программы" << '\n' << '\n';

}

void ShowCount(FilmLib _flmlb) // функция вывода текущего числа фильмов в фильмотеке в консоль
{
	cout << "Число фильмов в фильмотеке: " << _flmlb.GetCount() << '\n' << '\n';
}

Film InputNewFilm() // функция ввода информации о новом фильме
{
	Film input;
	cout << "Введите нзвание фильма: ";
	cin.ignore();
	getline(cin, input.name);
	cout << "Его режиссер: ";
	getline(cin, input.producer);
	cout << "Сценарист: ";
	getline(cin, input.swriter);
	cout << "Композитор: ";
	getline(cin, input.composer);
	cout << "Дата выхода в прокат" << '\n';
	cout << "День: ";
	cin >> input.day;
	cout << "Месяц: ";
	cin >> input.month;
	cout << "Год: ";
	cin >> input.year;
	cout << "Сборы (в рублях): ";
	cin >> input.box_office;
	return input;
}