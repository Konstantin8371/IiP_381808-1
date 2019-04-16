#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Film // ���������, ���������� ���������� �� ����� ������ �� ����������
{
	string name; // �������� ������
	string producer; // ��������
	string swriter; // ��������
	string composer; // ����������
	// ���� ������ � ������
		int day; 
		int month;
		int year;
	// �����
	int box_office;
};

class FilmLib
{
	Film *FilmArray;
	int count; // ����� ������ � ����������
	int buffSize; // ����� ����� � ������� 

public:

	void ProverkaVvodaRus(const string& _str); // ��� �������� ����� ������������� ���� �������� �������� ��� ����, ���������� ����������� ����������
	void AddFilm(const Film& _flm); // ���������� ������ � ����������
	int NameSearch(const string& _name); // ����� ������ �� ��� ��������
	Film* ProducerSearch(const string& _name, int *_num, Film* _flm); // ����� ���� ������� ������ ���������
	Film* TimeSearch(int _year, int *_num, Film *flm); // ����� ���� �������, �������� � ������������ ����
	Film GetFilm(const int _count); // ����� ���������� ���������� �� ����� ������ �� ����������
	void ChangeSelectedFilm(const Film& _flm, int _cnt); // ������ ���������� � �������� ������
	int GetCount(); // ���������� ���������� ������� � ����������
	void DeleteSelectedFilm(int _cnt); // ������� ���������� ������ 
	void MaxBoxOffice(int *_num, Film *flm); // ����� ������������� ����� ������� � ����������� �������� �������
	void MaxBoxOffice(int *_num, Film *flm, const int& year); // ����� ������������� ����� �������, �������� � ���������� ����, � ����������� �������� �������

	FilmLib(); // ����������� �� ���������
	FilmLib(const FilmLib& _flmlb); // ����������� �����������
	~FilmLib(); // ���������� 

	FilmLib& operator= (const FilmLib& _flmlb); // ���������� �������� ������������
	friend ostream& operator<< (ostream& _out, const FilmLib& _flmlb); // ���������� �������� ������ � �����
	friend istream& operator>> (istream& _in, FilmLib& _flmlb);        // ����� �� ������ 
};

ostream& operator<< (ostream& _out, const Film& _flm); // ��� �� ��� ��������� Film
istream& operator>> (istream& _in, Film& _flm);        //
int StrToInt(const string& _str); // ������ �������� �������� ���������� ����������, ���������� ���������� � ����� � ���������� ���� int