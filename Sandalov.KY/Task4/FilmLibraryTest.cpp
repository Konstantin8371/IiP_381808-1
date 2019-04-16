#include "FilmLibrary.h"
#include <conio.h>
#include <fstream>
#include <Windows.h>

void ShowMenu(); // �������� �������, ��������� � ������� ������� ���� ���������
void ShowCount(FilmLib _flmlb); // �������� �������, ��������� � ������� ������� ����� �������
Film InputNewFilm(); // �������� �������, 

int main()
{
	SetConsoleCP(1251); //������������� ��������� ����� �� ������� � �� ��������� ����
	SetConsoleOutputCP(1251); //������������� ��������� ������ �� �������
	
	FilmLib first_lib; // �������� ������ ������ FilmLib
	Film input; // ���������� ���� Film, ������� ������������ ��� ����� ���������� � ����� ������
	
	while (true)
	{
		string menu; // � �������������� ������ ���������� �������������� ����� ������ ����
	dt: // ����� ��� ��������� goto
		ShowCount(first_lib);
		ShowMenu();
		cout << "�������� ����� ����: ";
		
		try // ���������� ����������, ������� ��������� � ��� ������, ���� ������������ ������ ����� � ������ ������ ���� ����� �������� ������� ���������� �������
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
			cout << "������ ������ ��� � ����" << '\n';
			cout << '\n' << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls"); // ������� ������� � ������ ������� ����, ������� � ����� dt: 
			goto dt; // ������� � ����� dt:
		}

		int mn = StrToInt(menu); // ������ �������� �������� ���������� ����������, ���������� ���������� � ����� � ���������� ���� int

		string adr, name; // adr ������������ ��� ����� ����, �� �������� ����. ���� �������, name - ���������� ����� ��������� ��� �������� ������
		string Y_N; // ����������, ����������� ����� ������������ �� �������
		ifstream in;  // ���������� ��� ������ �
		ofstream out; // ������ ������� �� ������
		int cnt = 0, year;
		Film *Arr = NULL;

		switch (mn) // �������� switch, ����������� ����������� ����� ������ ����
		{
		case 0: // ����� �� ���������

			return 0;

		case 1: // ���������� ���������� �� �����

			system("cls");
			ShowCount(first_lib);
			cout << "������� ���� � �����: ";
			cin >> adr;
			while (adr.find(".txt") == string::npos) // ���������, ���� �� � ��������� ���� ".txt"
			{
				cout << "�� ������� ������������ ����" << '\n';
				cout << "������� ���� � �����: ";
				cin >> adr;
			}
			in.open(adr);

			in >> first_lib;

			system("cls");
			break;

		case 2: // ��������� ���������� � ����

			system("cls");
			ShowCount(first_lib);
			out.open("output.txt");
			out << first_lib;
			cout << "���� ������� ��������" << '\n';
			cout << '\n' << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			break;

		case 3:  // ���������� ������ ������ � ����������

			system("cls");
			ShowCount(first_lib);
			input = InputNewFilm();
			first_lib.AddFilm(input);

			break;

		case 4: // ������������ ����� ������ �� ��������, ��� ������� � ���������� ��������� ���������, ��, ������� ��� � ������������ ����������� ������� �����, ������� ����� �� �������� ��� �� �������� ��� ������
			    // ��, ��������� ��������� �������, ��� ��� ����� � ��� �������������� ���� � �� �� ��������, ����� �� ��������(�� � ���� ���������, ����������, ��� ��� ����� ���� ������ � ����������� ����������)
			system("cls");
			ShowCount(first_lib);
		ch1:
			cout << "������� ��� ������, ������� ������ �� �����: ";
			cin.ignore();
			getline(cin, name);
			try //���������� ����������, ������� ��������� � ��� ������, ���� ������������ ����� ���� �������� �������� � ���� �������� ������� ���-�� ���
			{
				first_lib.ProverkaVvodaRus(name);
			}
			catch (int a)
			{
				cout << "���������� ������ �����, ��������� ������ ����� �������� ��������" << endl;
				goto ch1;
			}
			if (first_lib.NameSearch(name) == -1) // ���� ������ ������ ��� � ����������, ������� ��������������� ��������� 
			{
				cout << "������ ������ ��� � ����������" << '\n';
				
			}
			else // � ��������� ������, ������� ��� ������ � ���������� ��������� � �������
			{
				cnt = 0;
				while (first_lib.GetFilm(first_lib.NameSearch(name) + cnt).name == first_lib.GetFilm(first_lib.NameSearch(name)).name)
				{
					cout << cnt + 1 << ") " << first_lib.GetFilm(first_lib.NameSearch(name) + cnt) << '\n';
					cnt++;
				}

				cout << "������ �������� ������ ������?[Yes/No]: "; // ������������� ����������� �������� ��� ������� ��������� �� ����������� ������ ����� ����� 
				cin >> Y_N;
				if (Y_N == "Yes")
				{
					cout << "�������� ����� ���� ������, ������ �������� ������ �� ��������: ";
					cin >> cnt;
					cout << "���� ���������� �������" << '\n';
					cout << "1) ������� �����" << '\n';
					cout << "2) �������� ������ ������" << '\n';
					cout << "������� ����� ������� ������: ";
					cin >> Y_N;
					if (Y_N == "2")
					{
						first_lib.ChangeSelectedFilm(InputNewFilm(), first_lib.NameSearch(name) + cnt - 1);
					}
					else
					{
						first_lib.DeleteSelectedFilm(first_lib.NameSearch(name) + cnt - 1);
					}
					cout << "������ � ������ ��������";
				}
			}
			cout << '\n' << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			break;

		case 5: // ������� ��� ������ ���������� ��������, ���� ����� ����
			system("cls");
			ShowCount(first_lib);
		ch2:
			cout << "������� ��� ���������, ������ �������� ������ �� �����: ";
			cin.ignore();
			getline(cin, name);
			try
			{
				first_lib.ProverkaVvodaRus(name);
			}
			catch (int a)
			{
				cout << "���������� ������ �����, ��������� ������ ����� �������� ��������" << endl;
				goto ch2;
			}
			Arr = first_lib.ProducerSearch(name, &cnt, Arr);
			if (cnt == 0)
			{
				cout << "������� ������ ��������� � ���������� ���" << '\n';
				
			}
			else
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 6: // ������� ��� ������, �������� � ������ � ��������� ����, ���� ����� ����
			system("cls");
			ShowCount(first_lib);
			cout << "������� ���, ����� ����������, ����� � ��� ����� ����� ������: ";
			cin >> year;
			Arr = first_lib.TimeSearch(year, &cnt, Arr);
			if (cnt == 0)
			{
				cout << "������� ����� ���� � ���������� ���" << '\n';
				
			}
			else
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 7: // ������ �������� ����� ������� � ������������� �������
			system("cls");
			ShowCount(first_lib);
			cout << "������� ����� ������� � ����������� �������, ������� ������ �� ������� �� �����: ";
			cin >> cnt;
			Arr = new Film[cnt];
			first_lib.MaxBoxOffice(&cnt, Arr);
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		case 8: // ������ �������� ����� ������� � ������������� ������� �������� � ������������ ����
			system("cls");
			ShowCount(first_lib);
			cout << "������� ���: ";
			cin >> year;
			cout << "������� ����� ������� � ����������� ������� � ��������� ����, ������� ������ �� ������� �� �����: ";
			cin >> cnt;
			
			Arr = new Film[cnt];
			first_lib.MaxBoxOffice(&cnt, Arr, year);
			for (int i = 0; i < cnt; ++i)
			{
				cout << Arr[i] << endl;
			}
			cout << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			delete[] Arr;
			break;

		default: // ������� ��������� � ���, ��� ������ ������ ���� ���, ���� �� ����� ������ �� ���� �� ������
			system("cls");
			cout << "������ ������ ��� � ����" << endl;
			cout << endl << "����� ��������� �� ������� �����, ������� �� ������� Enter";
			_getch();
			system("cls");
			break;
		}

	}
}

void ShowMenu() // ������� ������ ���� � �������
{

	cout << "1) ������� ���������� �� �����" << '\n';
	cout << "2) ��������� ���������� � ����" << '\n';
	cout << "3) �������� ����� � ����������" << '\n';
	cout << "4) ���� ������ �����, �������/�������� ���" << '\n';
	cout << "5) ������ ��� ������ ��������� ���������" << '\n';
	cout << "6) ������ �� ������, �������� � ������ � ��������� ����" << '\n';
	cout << "7) ������ �������� ����� ������� � ����������� �������" << '\n';
	cout << "8) ������ �������� ����� ������� � ����������� ������� � ��������� ����" << '\n';
	cout << "0) ����� �� ���������" << '\n' << '\n';

}

void ShowCount(FilmLib _flmlb) // ������� ������ �������� ����� ������� � ���������� � �������
{
	cout << "����� ������� � ����������: " << _flmlb.GetCount() << '\n' << '\n';
}

Film InputNewFilm() // ������� ����� ���������� � ����� ������
{
	Film input;
	cout << "������� ������� ������: ";
	cin.ignore();
	getline(cin, input.name);
	cout << "��� ��������: ";
	getline(cin, input.producer);
	cout << "���������: ";
	getline(cin, input.swriter);
	cout << "����������: ";
	getline(cin, input.composer);
	cout << "���� ������ � ������" << '\n';
	cout << "����: ";
	cin >> input.day;
	cout << "�����: ";
	cin >> input.month;
	cout << "���: ";
	cin >> input.year;
	cout << "����� (� ������): ";
	cin >> input.box_office;
	return input;
}