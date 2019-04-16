#pragma once
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Film // структура, содержащая информацию об одном фильме из фильмотеки
{
	string name; // название фильма
	string producer; // режиссер
	string swriter; // сценарст
	string composer; // композитор
	// дата выхода в прокат
		int day; 
		int month;
		int year;
	// сборы
	int box_office;
};

class FilmLib
{
	Film *FilmArray;
	int count; // число фиьмов в фильмотеке
	int buffSize; // запас места в словаре 

public:

	void ProverkaVvodaRus(const string& _str); // для проверки ввода пользователем слов русского алфавита или цифр, приисходит возбуждение исключений
	void AddFilm(const Film& _flm); // добавление фильма в фильмотеку
	int NameSearch(const string& _name); // поиск фильма по его названию
	Film* ProducerSearch(const string& _name, int *_num, Film* _flm); // поиск всех фильмов одного режиссера
	Film* TimeSearch(int _year, int *_num, Film *flm); // поиск всех фильмов, вышедших в определенном году
	Film GetFilm(const int _count); // метод возвращает информацию об одном фильме из фильмотеки
	void ChangeSelectedFilm(const Film& _flm, int _cnt); // меняет информацию о выбраном фильме
	int GetCount(); // возвращает количество фильмов в фильмотеке
	void DeleteSelectedFilm(int _cnt); // удалене выбранного фильма 
	void MaxBoxOffice(int *_num, Film *flm); // поиск определенного числа фильмов с максимально большими сборами
	void MaxBoxOffice(int *_num, Film *flm, const int& year); // поиск определенного числа фильмов, вышедших в конкретном году, с максимально большими сборами

	FilmLib(); // конструктор по умолчанию
	FilmLib(const FilmLib& _flmlb); // конструктор копирования
	~FilmLib(); // деструктор 

	FilmLib& operator= (const FilmLib& _flmlb); // перегрузка операции присваивания
	friend ostream& operator<< (ostream& _out, const FilmLib& _flmlb); // перегрузка операции вывода в поток
	friend istream& operator>> (istream& _in, FilmLib& _flmlb);        // ввода из потока 
};

ostream& operator<< (ostream& _out, const Film& _flm); // так же для структуры Film
istream& operator>> (istream& _in, Film& _flm);        //
int StrToInt(const string& _str); // фукция перевода значения строоковой переменной, содержащей информацию о числе в переменную типа int